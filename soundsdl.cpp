#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <cmath>

#include "soundsdl.h"

const int SAMPLE_RATE = 44100;
const int AMPLITUDE = 28000;
const double FREQUENCY = 440.0;

void audioCallBack(void* userdata, Uint8* stream, int len) {
    static double phase = 0.0;
    double increment = (2.0 * M_PI * FREQUENCY) / SAMPLE_RATE;
}