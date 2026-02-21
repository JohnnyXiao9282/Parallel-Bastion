#pragma once

#include <chrono>

namespace Core {

class Time {
public:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<double>;
    using TimePoint = std::chrono::time_point<Clock>;

    Time();

    void update();
    void reset();

    double getDeltaTime() const { return m_deltaTime; }
    double getTotalTime() const { return m_totalTime; }
    double getFPS() const { return m_fps; }
    int getFrameCount() const { return m_frameCount; }

private:
    TimePoint m_startTime;
    TimePoint m_lastFrameTime;
    TimePoint m_currentFrameTime;
    
    double m_deltaTime;
    double m_totalTime;
    double m_fps;
    int m_frameCount;
    double m_fpsUpdateTimer;
    int m_fpsFrameCount;
};

} // namespace Core
