#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <cmath>

#include "soundsdl.h"
#include "logger.h"

const int SAMPLE_RATE = 44100;
const int AMPLITUDE = 28000;
const double FREQUENCY = 440.0;

void audioCallBack(void* userdata, Uint8* stream, int len) {
    static double phase = 0.0;
    double increment = (2.0 * M_PI * FREQUENCY) / SAMPLE_RATE;

    for (int i = 0; i < len; i += 2) {
        short sample = static_cast<short>(AMPLITUDE * sin(phase));
        phase += increment;

        if (phase > 2.0 * M_PI) {
            phase -= 2.0 * M_PI;
        }

        stream[i] = sample & 0xFF;
        stream[i + 1] = (sample >> 8) & 0xFF;
    }
}

TSoundSDL::TSoundSDL() {
    m_logger = TLogger::getInstance();
}

TSoundSDL::~TSoundSDL() {

}

void TSoundSDL::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::string errorSdl(SDL_GetError());
        m_logger->log("SDL Sound Init Error: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }
}