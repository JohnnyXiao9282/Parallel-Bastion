#pragma once

#include "GameLoop.h"
#include "../engine/Renderer.h"
#include "../engine/EventBus.h"
#include "../concurrency/ThreadPool.h"
#include <memory>
#include <string>

namespace Core {

class Application {
public:
    Application(const std::string& title, int width, int height);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();
    void shutdown();

    Engine::Renderer& getRenderer() { return *m_renderer; }
    Engine::EventBus& getEventBus() { return *m_eventBus; }
    GameLoop& getGameLoop() { return m_gameLoop; }

private:
    bool pollEvents();
    void fixedUpdate(double dt);
    void render();

    std::unique_ptr<Engine::Renderer> m_renderer;
    std::unique_ptr<Engine::EventBus> m_eventBus;
    GameLoop m_gameLoop;
    std::unique_ptr<Concurrency::ThreadPool> m_threadPool;
    bool m_shouldQuit;

    // Player 1 (arrow keys) position
    int m_playerX = 5;
    int m_playerY = 5;
    // Player 2 (WASD) position
    int m_player2X = 10;
    int m_player2Y = 5;
};

} // namespace Core
