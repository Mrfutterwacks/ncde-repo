#!/usr/bin/env python3
"""ncde-vesper-seed-mitre.py — seed KickassGuard's ChromaDB 'mitre-attack' collection.

TARGET: /usr/local/lib/ncde/ncde-vesper-seed-mitre.py  (0755, root:root)
RUN BY: ncde-vesper-provision.sh, via /opt/ncde-chroma/bin/python (has chromadb).

Parses the MITRE ATT&CK enterprise STIX bundle (enterprise-attack.json), embeds one
document per non-deprecated technique with local Ollama 'nomic-embed-text', and upserts
into the RUNNING chroma server (HttpClient -> 127.0.0.1:8000), collection 'mitre-attack'
— the same store + collection name KickassGuard's ChromaClient.queryMitre() reads.

Robust + idempotent: retries embeds, commits in small batches, and RESUMES (skips
techniques already stored) so a hiccup never loses progress and a re-run is cheap.
Exit 0 = collection fully seeded; exit 1 = incomplete (caller retries next boot).

Adapted from ~/ncde-staging/vesper/brain/seed_mitre.py (which used a file-local
PersistentClient); this variant targets the live HTTP server so the data lands where
the daemon queries it.
"""
import argparse, json, sys, time, urllib.request

ap = argparse.ArgumentParser()
ap.add_argument("--stix",   default="/usr/lib/ncde/vesper/enterprise-attack.json")
ap.add_argument("--host",   default="127.0.0.1")
ap.add_argument("--port",   type=int, default=8000)
ap.add_argument("--ollama", default="http://127.0.0.1:11434")
ap.add_argument("--embed",  default="nomic-embed-text")
ap.add_argument("--batch",  type=int, default=25)
A = ap.parse_args()

EMBED_URL = A.ollama.rstrip("/") + "/api/embeddings"


def embed(text, tries=4):
    last = None
    for k in range(tries):
        try:
            body = json.dumps({"model": A.embed, "prompt": text, "keep_alive": "30m"}).encode()
            req = urllib.request.Request(EMBED_URL, data=body,
                                         headers={"Content-Type": "application/json"})
            with urllib.request.urlopen(req, timeout=180) as r:
                return json.load(r)["embedding"]
        except Exception as e:
            last = e
            print(f"[seed]   embed retry {k+1}/{tries}: {e}", flush=True)
            time.sleep(3)
    raise last


# ---- connect to the running chroma server ----
try:
    import chromadb
    from chromadb.config import Settings
except Exception as e:
    print(f"[seed] FATAL: chromadb not importable: {e}", flush=True)
    sys.exit(1)

try:
    client = chromadb.HttpClient(host=A.host, port=A.port,
                                 settings=Settings(anonymized_telemetry=False))
    client.heartbeat()
except Exception as e:
    print(f"[seed] FATAL: cannot reach chroma at {A.host}:{A.port}: {e}", flush=True)
    sys.exit(1)

col = client.get_or_create_collection(
    name="mitre-attack",
    metadata={"source": "mitre enterprise attack", "embed": A.embed})

# ---- parse STIX: one document per (non-deprecated) technique ----
try:
    data = json.load(open(A.stix))
except Exception as e:
    print(f"[seed] FATAL: cannot read STIX {A.stix}: {e}", flush=True)
    sys.exit(1)

seen, techniques = set(), []
for o in data.get("objects", []):
    if o.get("type") != "attack-pattern":
        continue
    if o.get("revoked") or o.get("x_mitre_deprecated"):
        continue
    tid = next((r.get("external_id") for r in o.get("external_references", [])
                if r.get("source_name") == "mitre-attack"), None)
    if not tid or tid in seen:
        continue
    seen.add(tid)
    name = o.get("name", "")
    desc = (o.get("description", "") or "").strip()
    tactics = [p.get("phase_name") for p in o.get("kill_chain_phases", [])
               if p.get("kill_chain_name") == "mitre-attack"]
    doc = f"{tid} {name}. Tactics: {', '.join(tactics)}. {desc}"
    techniques.append((tid, name, tactics, doc))
print(f"[seed] techniques parsed: {len(techniques)}", flush=True)
if not techniques:
    print("[seed] FATAL: zero techniques parsed — bad STIX?", flush=True)
    sys.exit(1)

# ---- resume: skip ids already stored ----
have = set(col.get(include=[])["ids"])
todo = [t for t in techniques if t[0] not in have]
print(f"[seed] already stored: {len(have)}  |  to embed now: {len(todo)}", flush=True)
if not todo:
    print(f"[seed] DONE (already complete): {col.count()} techniques in 'mitre-attack'.", flush=True)
    sys.exit(0)

# ---- warm the embed model once ----
try:
    embed("warmup")
except Exception as e:
    print(f"[seed] FATAL: embeddings unavailable ({A.embed}): {e}", flush=True)
    sys.exit(1)

ids, docs, metas, embs = [], [], [], []
t0 = time.time()


def flush():
    if ids:
        col.add(ids=ids, documents=docs, metadatas=metas, embeddings=embs)
        ids.clear(); docs.clear(); metas.clear(); embs.clear()


try:
    for i, (tid, name, tactics, doc) in enumerate(todo):
        embs.append(embed(doc[:1600]))
        ids.append(tid); docs.append(doc)
        metas.append({"tid": tid, "name": name, "tactics": ",".join(tactics)})
        if len(ids) >= A.batch:
            flush()
            print(f"[seed] committed {i+1}/{len(todo)}  "
                  f"(total stored {col.count()}, {time.time()-t0:.0f}s)", flush=True)
    flush()
except Exception as e:
    flush()  # persist what we got; resume covers the rest next run
    print(f"[seed] INCOMPLETE: {e}  (committed {col.count()} so far — will resume)", flush=True)
    sys.exit(1)

print(f"[seed] DONE: {col.count()} techniques in 'mitre-attack' "
      f"({time.time()-t0:.0f}s)", flush=True)
sys.exit(0)
