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
};
#endif