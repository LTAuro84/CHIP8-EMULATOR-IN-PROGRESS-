#ifndef __DISPLAYSDL_H__
#define __DISPLAYSDL_H__
#include <cstdint>
#include <SDL2/SDL.h>
#include "display.h"
#include "logger.h"
using namespace std;

class TDisplaySDL : public TDisplay {
    SDL_Window* window; 
    SDL_Surface* surface;

    shared_ptr<TLogger> m_loggerInstance;

public:
    TDisplaySDL();
    ~TDisplaySDL();

    virtual void init() override;
    virtual void draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height) override;
    virtual void update() override;
    virtual void deinit() override;

};

#endif