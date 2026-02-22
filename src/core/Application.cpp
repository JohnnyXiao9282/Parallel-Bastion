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
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return false;
            }
        }
    }
    
    return true;
}

void Application::fixedUpdate(double dt) {
    (void)dt;
    // Submit a dummy task to thread pool
    auto future = m_threadPool->enqueue([] {
        Utils::Logger::info("ThreadPool task running");
    });
    // Optionally wait for completion (for demo)
    future.get();
}

void Application::render() {
    m_renderer->clear(0, 0, 0, 255);
    m_renderer->renderGrid(32);
    m_renderer->present();
}

} // namespace Core
