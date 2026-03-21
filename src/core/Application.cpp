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
                    break;
                case SDLK_DOWN:
                    m_playerY++;
                    break;
                case SDLK_LEFT:
                    if (m_playerX > 0) m_playerX--;
                    break;
                case SDLK_RIGHT:
                    m_playerX++;
                    break;
                // Player 2: WASD
                case SDLK_w:
                    if (m_player2Y > 0) m_player2Y--;
                    break;
                case SDLK_s:
                    m_player2Y++;
                    break;
                case SDLK_a:
                    if (m_player2X > 0) m_player2X--;
                    break;
                case SDLK_d:
                    m_player2X++;
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
    // Submit a dummy task to thread pool (non-blocking demo)
    m_threadPool->enqueue([] {
        Utils::Logger::info("ThreadPool task running");
    });
}

void Application::render() {
    m_renderer->clear(0, 0, 0, 255);
    m_renderer->renderGrid(32);
    int cellSize = 32;
    // Player 1: green
    int px1 = m_playerX * cellSize;
    int py1 = m_playerY * cellSize;
    m_renderer->drawRect(px1, py1, cellSize, cellSize, 0, 200, 0, 255);
    // Player 2: blue
    int px2 = m_player2X * cellSize;
    int py2 = m_player2Y * cellSize;
    m_renderer->drawRect(px2, py2, cellSize, cellSize, 0, 0, 200, 255);
    m_renderer->present();
}

}
