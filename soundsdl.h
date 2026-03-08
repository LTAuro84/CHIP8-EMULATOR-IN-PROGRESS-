#ifndef __SOUNDSDL_H__
#define __SOUNDSDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <memory>
#include "logger.h"
#include "sound.h"

using namespace std;

class TSoundSDL : public TSound {
    SDL_AudioSpec audioSpec;

    shared_ptr<TLogger> m_logger;

    public:
        TSoundSDL();
        ~TSoundSDL();

        virtual void init() override;
        virtual void playTune() override;
        virtual void pauseTune() override;
        virtual void deinit() override;
};

#endif