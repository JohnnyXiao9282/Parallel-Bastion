// Draw a stylized Bastion symbol (target) at grid cell
void Renderer::drawBastionSymbol(int x, int y, int cellSize) {
    // Draw a gold/yellow filled rectangle with a black border and a 'B' shape using lines
    int px = x * cellSize;
    int py = y * cellSize;
    // Filled rect (gold)
    SDL_Rect fillRect = { px+2, py+2, cellSize-4, cellSize-4 };
    SDL_SetRenderDrawColor(m_renderer, 220, 180, 30, 255);
    SDL_RenderFillRect(m_renderer, &fillRect);
    // Border (black)
    SDL_Rect borderRect = { px+2, py+2, cellSize-4, cellSize-4 };
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(m_renderer, &borderRect);
    // Draw a 'B' using lines (black)
    int cx = px + cellSize/2;
    int cy = py + cellSize/2;
    int r = cellSize/4;
    // Vertical line
    SDL_RenderDrawLine(m_renderer, px+cellSize/4, py+cellSize/4, px+cellSize/4, py+cellSize*3/4);
    // Top curve
    SDL_RenderDrawLine(m_renderer, px+cellSize/4, py+cellSize/4, px+cellSize*3/4, py+cellSize/4);
    SDL_RenderDrawLine(m_renderer, px+cellSize*3/4, py+cellSize/4, px+cellSize*3/4, py+cellSize/2);
    SDL_RenderDrawLine(m_renderer, px+cellSize*3/4, py+cellSize/2, px+cellSize/4, py+cellSize/2);
    // Bottom curve
    SDL_RenderDrawLine(m_renderer, px+cellSize/4, py+cellSize/2, px+cellSize*3/4, py+cellSize/2);
    SDL_RenderDrawLine(m_renderer, px+cellSize*3/4, py+cellSize/2, px+cellSize*3/4, py+cellSize*3/4);
    SDL_RenderDrawLine(m_renderer, px+cellSize*3/4, py+cellSize*3/4, px+cellSize/4, py+cellSize*3/4);
}
#include "Renderer.h"
#include "../utils/Logger.h"
#include <stdexcept>

namespace Engine {

Renderer::Renderer(const std::string& title, int width, int height)
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_width(width)
    , m_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
    }

    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!m_window) {
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow failed: " + std::string(SDL_GetError()));
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!m_renderer) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::runtime_error("SDL_CreateRenderer failed: " + std::string(SDL_GetError()));
    }

    Utils::Logger::info("Renderer initialized: " + std::to_string(width) + "x" + std::to_string(height));
}

Renderer::~Renderer() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
    SDL_Quit();
}

void Renderer::clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderClear(m_renderer);
}

void Renderer::present() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::drawRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(m_renderer, &rect);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}

void Renderer::renderGrid(int cellSize) {
    SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
    
    for (int x = 0; x < m_width; x += cellSize) {
        SDL_RenderDrawLine(m_renderer, x, 0, x, m_height);
    }
    
    for (int y = 0; y < m_height; y += cellSize) {
        SDL_RenderDrawLine(m_renderer, 0, y, m_width, y);
    }
}

} // namespace Engine
