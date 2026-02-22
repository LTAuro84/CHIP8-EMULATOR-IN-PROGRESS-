#include <cstdint>
#include <SDL2/SDL.h>
#include "displaysdl.h"
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
}