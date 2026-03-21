
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

    // Target (enemy) position
    int m_targetX = 0;
    int m_targetY = 0;

    // Player 1 (arrow keys) position and direction
    int m_playerX = 5;
    int m_playerY = 5;
    enum class Dir { Up, Down, Left, Right };
    Dir m_playerDir = Dir::Up;
    // Player 1 shot
    bool m_playerShotActive = false;
    int m_playerShotX = 0;
    int m_playerShotY = 0;
    Dir m_playerShotDir = Dir::Up;

    // Player 2 (WASD) position and direction
    int m_player2X = 10;
    int m_player2Y = 5;
    Dir m_player2Dir = Dir::Up;
    // Player 2 shot
    bool m_player2ShotActive = false;
    int m_player2ShotX = 0;
    int m_player2ShotY = 0;
    Dir m_player2ShotDir = Dir::Up;

    // Score
    int m_score1 = 0;
    int m_score2 = 0;

    // Grid size
    static constexpr int GRID_W = 40;
    static constexpr int GRID_H = 22;

    void spawnTarget();
    bool isOccupied(int x, int y) const;
};

} // namespace Core
