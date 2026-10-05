#!/usr/bin/env python3
"""
Process panel.png to create pre-scaled 9-slice frame asset.
- Zero stray alpha-1 pixels in inner clear zone
- Pre-scale to panel height (32px inner clear zone for top panel)
- Save as panel-frame.png in ncde asset directory
"""

from PIL import Image

def process_panel():
    # Load source panel.png
    src_path = '/run/media/stephen/NCDE-BACKUP/my-project/source-recovery/pending-art/panel.png'
    img = Image.open(src_path).convert('RGBA')
    w, h = img.size
    print(f"Source: {w}x{h}")
    pixels = img.load()

    # Verified measurements from art.md:
    inner_left = 258
    inner_right = 1911
    inner_top = 186
    inner_bottom = 531
    inner_width = inner_right - inner_left + 1  # 1654
    inner_height = inner_bottom - inner_top + 1  # 346

    rail_left = 599
    rail_right = 1568
    rail_width = rail_right - rail_left + 1  # 970

    top_rail_top = 129
    top_rail_bottom = 185
    top_rail_height = top_rail_bottom - top_rail_top + 1  # 57

    bottom_rail_top = 531
    bottom_rail_bottom = 579
    bottom_rail_height = bottom_rail_bottom - bottom_rail_top + 1  # 49

    left_cap_right = 257
    right_cap_left = 1912

    print(f"Inner clear zone: ({inner_left},{inner_top}) - ({inner_right},{inner_bottom}) = {inner_width}x{inner_height}")
    print(f"Straight rails: x {rail_left}..{rail_right} ({rail_width}px)")
    print(f"Top rail: y {top_rail_top}..{top_rail_bottom} ({top_rail_height}px)")
    print(f"Bottom rail: y {bottom_rail_top}..{bottom_rail_bottom} ({bottom_rail_height}px)")
    print(f"Left cap: x 0..{left_cap_right}, Right cap: x {right_cap_left}..{w-1}")

    # Zero stray alpha 1..7 pixels inside inner clear zone
    stray_count = 0
    for y in range(inner_top, inner_bottom + 1):
        for x in range(inner_left, inner_right + 1):
            r, g, b, a = pixels[x, y]
            if 0 < a < 8:
                pixels[x, y] = (r, g, b, 0)
                stray_count += 1
    print(f"Stray alpha 1-7 pixels in inner zone: {stray_count}")

    # Also zero stray pixels in the rail stretch regions
    stray_tr = 0
    for y in range(top_rail_top, top_rail_bottom + 1):
        for x in range(rail_left, rail_right + 1):
            r, g, b, a = pixels[x, y]
            if 0 < a < 8:
                pixels[x, y] = (r, g, b, 0)
                stray_tr += 1
    print(f"Stray in top rail stretch: {stray_tr}")

    stray_br = 0
    for y in range(bottom_rail_top, bottom_rail_bottom + 1):
        for x in range(rail_left, rail_right + 1):
            r, g, b, a = pixels[x, y]
            if 0 < a < 8:
                pixels[x, y] = (r, g, b, 0)
                stray_br += 1
    print(f"Stray in bottom rail stretch: {stray_br}")

    # Now pre-scale to panel height.
    target_inner_height = 32
    scale = target_inner_height / inner_height
    print(f"Scale factor: {scale:.6f}")

    new_w = int(round(w * scale))
    new_h = int(round(h * scale))
    print(f"Pre-scaled size: {new_w}x{new_h}")

    # Use high-quality lanczos resampling
    img_scaled = img.resize((new_w, new_h), Image.LANCZOS)

    # Save pre-scaled asset
    dst_path = '/run/media/stephen/NCDE-BACKUP/my-project/files/full-patch-20260711/src/usr/share/ncde/panel-frame.png'
    img_scaled.save(dst_path)
    print(f"Saved to {dst_path}")

    # Also compute the 9-slice border values for the scaled image
    scaled_inner_left = int(round(inner_left * scale))
    scaled_inner_right = int(round(inner_right * scale))
    scaled_inner_top = int(round(inner_top * scale))
    scaled_inner_bottom = int(round(inner_bottom * scale))
    scaled_rail_left = int(round(rail_left * scale))
    scaled_rail_right = int(round(rail_right * scale))
    scaled_top_rail_top = int(round(top_rail_top * scale))
    scaled_top_rail_bottom = int(round(top_rail_bottom * scale))
    scaled_bottom_rail_top = int(round(bottom_rail_top * scale))
    scaled_bottom_rail_bottom = int(round(bottom_rail_bottom * scale))
    scaled_left_cap_right = int(round(left_cap_right * scale))
    scaled_right_cap_left = int(round(right_cap_left * scale))

    print(f"\nScaled measurements:")
    print(f"  Inner clear zone: x {scaled_inner_left}..{scaled_inner_right}, y {scaled_inner_top}..{scaled_inner_bottom}")
    print(f"  Straight rails: x {scaled_rail_left}..{scaled_rail_right}")
    print(f"  Top rail: y {scaled_top_rail_top}..{scaled_top_rail_bottom}")
    print(f"  Bottom rail: y {scaled_bottom_rail_top}..{scaled_bottom_rail_bottom}")
    print(f"  Left cap ends at x: {scaled_left_cap_right}")
    print(f"  Right cap starts at x: {scaled_right_cap_left}")
    print(f"  Image size: {new_w}x{new_h}")

    # For 9-slice BorderImage:
    border_left = scaled_left_cap_right + 1
    border_right = new_w - scaled_right_cap_left
    border_top = scaled_top_rail_bottom + 1
    border_bottom = new_h - scaled_bottom_rail_top

    print(f"\n9-slice border values for BorderImage:")
    print(f"  border.left: {border_left}")
    print(f"  border.right: {border_right}")
    print(f"  border.top: {border_top}")
    print(f"  border.bottom: {border_bottom}")

    print(f"\nFrame positioning (like dock):")
    print(f"  topOut: {border_top}")
    print(f"  bottomOut: {border_bottom}")
    print(f"  sideOut: 0 (full width panels)")
    print(f"  Frame height for 32px panel: {32 + border_top + border_bottom}")
    print(f"  Frame height for 30px panel: {30 + border_top + border_bottom}")

    return {
        'scale': scale,
        'new_w': new_w,
        'new_h': new_h,
        'border_left': border_left,
        'border_right': border_right,
        'border_top': border_top,
        'border_bottom': border_bottom,
        'inner_height': target_inner_height,
        'scaled_inner_top': scaled_inner_top,
        'scaled_inner_bottom': scaled_inner_bottom,
        'scaled_inner_left': scaled_inner_left,
        'scaled_inner_right': scaled_inner_right,
    }

if __name__ == '__main__':
    process_panel()