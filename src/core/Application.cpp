#include <random>
#include "Application.h"
#include "../utils/Logger.h"
#include <SDL2/SDL.h>

namespace Core {

Application::Application(const std::string& title, int width, int height)
    : m_shouldQuit(false)
{
    Utils::Logger::info("Initializing Application: " + title);
    m_renderer = std::make_unique<Engine::Renderer>(title, width, height);
    m_eventBus = std::make_unique<Engine::EventBus>();
    m_threadPool = std::make_unique<Concurrency::ThreadPool>(4);
    spawnTarget();
    Utils::Logger::info("Application initialized successfully");
}

Application::~Application() {
    Utils::Logger::info("Shutting down Application");
}

void Application::run() {
    Utils::Logger::info("Starting game loop");
    
    m_gameLoop.run(
        [this]() { return pollEvents(); },
        [this](double dt) { fixedUpdate(dt); },
        [this]() { render(); }
    );
    
    Utils::Logger::info("Game loop ended");
}

void Application::shutdown() {
    Utils::Logger::info("Shutdown requested");
    m_gameLoop.stop();
}

bool Application::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                // Player 1: Arrow keys
                case SDLK_ESCAPE:
                    return false;
                case SDLK_UP:
                    if (m_playerY > 0) m_playerY--;
                    m_playerDir = Dir::Up;
                    break;
                case SDLK_DOWN:
                    if (m_playerY < GRID_H-1) m_playerY++;
                    m_playerDir = Dir::Down;
                    break;
                case SDLK_LEFT:
                    if (m_playerX > 0) m_playerX--;
                    m_playerDir = Dir::Left;
                    break;
                case SDLK_RIGHT:
                    if (m_playerX < GRID_W-1) m_playerX++;
                    m_playerDir = Dir::Right;
                    break;
                case SDLK_SPACE:
                    if (!m_playerShotActive) {
                        m_playerShotActive = true;
                        m_playerShotX = m_playerX;
                        m_playerShotY = m_playerY;
                        m_playerShotDir = m_playerDir;
                    }
                    break;
                // Player 2: WASD
                case SDLK_w:
                    if (m_player2Y > 0) m_player2Y--;
                    m_player2Dir = Dir::Up;
                    break;
                case SDLK_s:
                    if (m_player2Y < GRID_H-1) m_player2Y++;
                    m_player2Dir = Dir::Down;
                    break;
                case SDLK_a:
                    if (m_player2X > 0) m_player2X--;
                    m_player2Dir = Dir::Left;
                    break;
                case SDLK_d:
                    if (m_player2X < GRID_W-1) m_player2X++;
                    m_player2Dir = Dir::Right;
                    break;
                case SDLK_f:
                    if (!m_player2ShotActive) {
                        m_player2ShotActive = true;
                        m_player2ShotX = m_player2X;
                        m_player2ShotY = m_player2Y;
                        m_player2ShotDir = m_player2Dir;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}

void Application::fixedUpdate(double dt) {
    (void)dt;
    // Move player 1 shot
    if (m_playerShotActive) {
        switch (m_playerShotDir) {
            case Dir::Up:    m_playerShotY--; break;
            case Dir::Down:  m_playerShotY++; break;
            case Dir::Left:  m_playerShotX--; break;
            case Dir::Right: m_playerShotX++; break;
        }
        // Out of bounds
        if (m_playerShotX < 0 || m_playerShotX >= GRID_W || m_playerShotY < 0 || m_playerShotY >= GRID_H) {
            m_playerShotActive = false;
        }
        // Hit target
        if (m_playerShotActive && m_playerShotX == m_targetX && m_playerShotY == m_targetY) {
            m_score1++;
            m_playerShotActive = false;
            spawnTarget();
        }
    }
    // Move player 2 shot
    if (m_player2ShotActive) {
        switch (m_player2ShotDir) {
            case Dir::Up:    m_player2ShotY--; break;
            case Dir::Down:  m_player2ShotY++; break;
            case Dir::Left:  m_player2ShotX--; break;
            case Dir::Right: m_player2ShotX++; break;
        }
        if (m_player2ShotX < 0 || m_player2ShotX >= GRID_W || m_player2ShotY < 0 || m_player2ShotY >= GRID_H) {
            m_player2ShotActive = false;
        }
        if (m_player2ShotActive && m_player2ShotX == m_targetX && m_player2ShotY == m_targetY) {
            m_score2++;
            m_player2ShotActive = false;
            spawnTarget();
        }
    }
}

void Application::render() {
    m_renderer->clear(0, 0, 0, 255);
    m_renderer->renderGrid(32);
    int cellSize = 32;
    // Draw target as a large gold square with a black border (bastion-like)
    int tx = m_targetX * cellSize;
    int ty = m_targetY * cellSize;
    // Filled gold square
    m_renderer->drawRect(tx+2, ty+2, cellSize*2-4, cellSize*2-4, 220, 180, 30, 255);
    // Black border
    m_renderer->drawRect(tx+2, ty+2, cellSize*2-4, cellSize*2-4, 0, 0, 0, 255);
    // Player 1: green
    int px1 = m_playerX * cellSize;
    int py1 = m_playerY * cellSize;
    m_renderer->drawRect(px1, py1, cellSize, cellSize, 0, 200, 0, 255);
    // Player 2: blue
    int px2 = m_player2X * cellSize;
    int py2 = m_player2Y * cellSize;
    m_renderer->drawRect(px2, py2, cellSize, cellSize, 0, 0, 200, 255);
    // Player 1 shot (yellow)
    if (m_playerShotActive) {
        int sx = m_playerShotX * cellSize;
        int sy = m_playerShotY * cellSize;
        m_renderer->drawRect(sx, sy, cellSize, cellSize, 255, 255, 0, 255);
    }
    // Player 2 shot (cyan)
    if (m_player2ShotActive) {
        int sx = m_player2ShotX * cellSize;
        int sy = m_player2ShotY * cellSize;
        m_renderer->drawRect(sx, sy, cellSize, cellSize, 0, 255, 255, 255);
    }
    m_renderer->present();
// Helper: check if a grid cell is occupied by a player
bool Application::isOccupied(int x, int y) const {
    return (x == m_playerX && y == m_playerY) || (x == m_player2X && y == m_player2Y);
// Helper: check if a grid cell is occupied by a player
bool Application::isOccupied(int x, int y) const {
    return (x == m_playerX && y == m_playerY) || (x == m_player2X && y == m_player2Y);
}

// Helper: spawn target at fixed location for debugging
void Application::spawnTarget() {
    m_targetX = 5;
    m_targetY = 5;
}

} // namespace Core
