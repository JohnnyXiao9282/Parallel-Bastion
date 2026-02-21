#include "GameLoop.h"
#include <thread>

namespace Core {

GameLoop::GameLoop()
    : m_isRunning(false)
    , m_accumulator(0.0)
{
}

void GameLoop::run(
    std::function<bool()> pollEvents,
    std::function<void(double)> fixedUpdate,
    std::function<void()> render
) {
    m_isRunning = true;
    m_time.reset();

    while (m_isRunning) {
        m_time.update();
        
        if (!pollEvents()) {
            m_isRunning = false;
            break;
        }

        m_accumulator += m_time.getDeltaTime();
        
        int updateSteps = 0;
        while (m_accumulator >= FIXED_TIMESTEP && updateSteps < MAX_FRAME_SKIP) {
            fixedUpdate(FIXED_TIMESTEP);
            m_accumulator -= FIXED_TIMESTEP;
            updateSteps++;
        }

        render();

        if (m_accumulator > FIXED_TIMESTEP * MAX_FRAME_SKIP) {
            m_accumulator = 0.0;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

} // namespace Core
