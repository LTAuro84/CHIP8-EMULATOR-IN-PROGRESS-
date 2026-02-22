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
}