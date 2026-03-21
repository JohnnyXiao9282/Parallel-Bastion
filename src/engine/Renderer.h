    // Draw a stylized Bastion symbol (target) at grid cell
    void drawBastionSymbol(int x, int y, int cellSize);
#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

namespace Engine {

class Renderer {
public:
    Renderer(const std::string& title, int width, int height);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void present();

    void drawRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void renderGrid(int cellSize);

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    SDL_Renderer* getSDLRenderer() { return m_renderer; }

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_width;
    int m_height;
};

} // namespace Engine
