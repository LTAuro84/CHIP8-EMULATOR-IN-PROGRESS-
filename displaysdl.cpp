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