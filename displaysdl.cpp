#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include "displaysdl.h"
#include "logger.h"
using namespace std;

TDisplaySDL::TDisplaySDL() {
    m_loggerInstance = TLogger::getInstance();
}

TDisplaySDL::~TDisplaySDL() {

}

void TDisplaySDL::init() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) { 
    string errorSdl(SDL_GetError());
    m_loggerInstance->log("SDL ERROR: " + errorSdl, ELogLevel::ERROR);
    exit(1);
    }

    window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    1280, 720, SDL_WINDOW_SHOWN);
    
    if (!window) {
        string errorWindow(SDL_GetError());
        m_loggerInstance->log("Window error: " + errorWindow, ELogLevel::ERROR);
        exit(1);
    }

    surface = SDL_GetWindowSurface(window);
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    if (x >= 0 && x < surface->w && y >= 0 && y < surface->h ) {
        Uint32 *pixels = (Uint32 *)surface->pixels;
        pixels[(y * surface->w) + x] = color;
    }
}

void TDisplaySDL::draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height) {
    uint8_t zoom = 10;

    if (SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
    }

    //Black
    Uint32 color = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
    SDL_FillRect(surface, NULL, color);

    //White
    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255); 
    Uint32 green = SDL_MapRGB(surface->format, 0, 255, 0);

    for (auto i=0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            if (framebuffer[i][j] == 1) {
                for (auto x = 0; x < zoom; x++) {
                    for (auto y = 0; y < zoom; y++) {
                        setPixel(surface, j * zoom + x, i * zoom + y, green);
                    }
                }
            }
        }
    }

    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

void TDisplaySDL::update() {
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    if (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            m_loggerInstance->log("Closing: ", ELogLevel::ERROR);
        }
    }
}

