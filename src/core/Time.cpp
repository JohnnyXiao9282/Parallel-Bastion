#include "Time.h"

namespace Core {

Time::Time()
    : m_deltaTime(0.0)
    , m_totalTime(0.0)
    , m_fps(0.0)
    , m_frameCount(0)
    , m_fpsUpdateTimer(0.0)
    , m_fpsFrameCount(0)
{
    m_startTime = Clock::now();
    m_lastFrameTime = m_startTime;
    m_currentFrameTime = m_startTime;
}

void Time::update() {
    m_currentFrameTime = Clock::now();
    
    Duration frameDuration = m_currentFrameTime - m_lastFrameTime;
    m_deltaTime = frameDuration.count();
    
    Duration totalDuration = m_currentFrameTime - m_startTime;
    m_totalTime = totalDuration.count();
    
    m_lastFrameTime = m_currentFrameTime;
    m_frameCount++;
    
    m_fpsUpdateTimer += m_deltaTime;
    m_fpsFrameCount++;
    
    if (m_fpsUpdateTimer >= 1.0) {
        m_fps = m_fpsFrameCount / m_fpsUpdateTimer;
        m_fpsUpdateTimer = 0.0;
        m_fpsFrameCount = 0;
    }
}

void Time::reset() {
    m_startTime = Clock::now();
    m_lastFrameTime = m_startTime;
    m_currentFrameTime = m_startTime;
    m_deltaTime = 0.0;
    m_totalTime = 0.0;
    m_frameCount = 0;
    m_fpsUpdateTimer = 0.0;
    m_fpsFrameCount = 0;
}

} // namespace Core
