#include <cstdint>
#include <SDL2/SDL.h>
#include "keyboardsdl.h"
#include "logger.h"

KeyboardSDL::KeyboardSDL() {
    m_logger = TLogger::getInstance();
}

KeyboardSDL::~KeyboardSDL() {

}

void KeyboardSDL::init() {
    
}