#pragma once

#include "Time.h"
#include <functional>

namespace Core {

class GameLoop {
public:
    GameLoop();
    ~GameLoop() = default;

    static constexpr double TARGET_FPS = 60.0;
    static constexpr double FIXED_TIMESTEP = 1.0 / TARGET_FPS;
    static constexpr int MAX_FRAME_SKIP = 5;

    void run(
        std::function<bool()> pollEvents,
        std::function<void(double)> fixedUpdate,
        std::function<void()> render
    );

    void stop() { m_isRunning = false; }
    bool isRunning() const { return m_isRunning; }

    const Time& getTime() const { return m_time; }

private:
    Time m_time;
    bool m_isRunning;
    double m_accumulator;
};

} // namespace Core
