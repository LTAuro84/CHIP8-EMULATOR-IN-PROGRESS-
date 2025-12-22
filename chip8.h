#ifndef __CHIP8_H__
#define __CHIP8_H__


#include <cstdint>
#include <iostream>

#include "logger.h"

#define NUM_KEYS 16
#define TOTAL_RAM 4096  //4kb of memory
#define STACK_SIZE 16   //16 return addresses
#define FONTSET_SIZE 80
#define TIMER_MAX 255
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#define CHIP8_RAM_START_ADDR 0x000
#define CHIP8_RAM_END_ADDR 0x1FF
#define PROGRAM_START_ADDR 0x200
#define PROGRAM_END_ADDR 0xFFF
using namespace std;

//fontset - shapes for the numbers and letters
const static uint8_t FONTSET[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class TCpu;

class TChip8 {
        friend class TCpu;

        //screem
        uint8_t m_screen[SCREEN_HEIGHT][SCREEN_WIDTH];

        //keyboard
        uint8_t m_keys[NUM_KEYS];
        bool m_key_pressed;

        //memory
        uint8_t m_ram[TOTAL_RAM];
        uint16_t m_stack[STACK_SIZE];

        //timer
        uint8_t m_delay_timer;
        uint8_t m_sound_timer;

        //control
        bool m_emulatorRunning;

        shared_ptr<TLogger> m_logger;

public:
    TChip8();
    ~TChip8();

    void init(string rom_path);
    void run();
    void deinit();
};

#endif