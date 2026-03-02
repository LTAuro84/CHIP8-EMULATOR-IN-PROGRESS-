#ifndef __KEYBOARDSDL_H__
#define __KEYBOARDSDL_H__

#include <cstdint>
#include <memory>
#include "keyboard.h"
#include "logger.h"
using namespace std;

class KeyboardSDL : public Keyboard {
    shared_ptr<TLogger> m_logger;

    public:
        KeyboardSDL();
        ~KeyboardSDL();

        virtual void init() override;
        virtual void update(uint8_t* key_map, bool* running) override;
        virtual void deinit() override;
};
#endif