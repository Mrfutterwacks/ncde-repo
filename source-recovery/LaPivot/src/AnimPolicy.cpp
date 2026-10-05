#include "AnimPolicy.h"

#include <algorithm>

AnimPolicy::AnimPolicy(QObject *parent)
    : QObject(parent)
{
    connect(this, &AnimPolicy::changed, this, &AnimPolicy::policyChanged);
}

int AnimPolicy::level() const
{
    return std::max(m_baseLevel, lowPower() ? int(Reduced) : int(Full));
}

bool AnimPolicy::lowPower() const
{
    return m_lowPowerCpu || m_lowPowerProfile || m_lowPowerMemory || m_lowPowerBattery;
}

void AnimPolicy::setFlag(bool &flag, bool on)
{
    if (flag == on)
        return;
    flag = on;
    emit changed();
}

void AnimPolicy::setLevel(int lvl)
{
    if (lvl == m_baseLevel)
        return;
    m_baseLevel = lvl;
    emit changed();
}

void AnimPolicy::setReduceMotion(bool on)
{
    if (on == m_reduceMotion)
        return;
    m_reduceMotion = on;
    reevaluate();
}

void AnimPolicy::reevaluate()
{
    emit changed();
}

void AnimPolicy::setThermalPressure(bool on) { setFlag(m_thermalPressure, on); }
void AnimPolicy::setDesktopObscured(bool on) { setFlag(m_desktopObscured, on); }
void AnimPolicy::setLowPowerCpu(bool on) { setFlag(m_lowPowerCpu, on); }
void AnimPolicy::setLowPowerProfile(bool on) { setFlag(m_lowPowerProfile, on); }
void AnimPolicy::setLowPowerMemory(bool on) { setFlag(m_lowPowerMemory, on); }
void AnimPolicy::setLowPowerBattery(bool on) { setFlag(m_lowPowerBattery, on); }

void AnimPolicy::onScreenSaverActivated(bool active)
{
    m_screenSaverActive = active;
    applyScreenIdle();
}

void AnimPolicy::onUserInputIdle(bool idle)
{
    m_userInputIdle = idle;
    applyScreenIdle();
}

void AnimPolicy::onVtActiveChanged(bool active)
{
    m_vtInactive = !active;
    applyScreenIdle();
}

void AnimPolicy::onSessionLocked()
{
    m_sessionLocked = true;
    applyScreenIdle();
}

void AnimPolicy::onSessionUnlocked()
{
    m_sessionLocked = false;
    applyScreenIdle();
}

void AnimPolicy::applyScreenIdle()
{
    setFlag(m_screenIdle, m_sessionLocked || m_vtInactive || m_screenSaverActive || m_userInputIdle);
}
