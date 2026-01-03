#include "cpu.h"
#include "chip8.h"
#include "logger.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

TChip8::TChip8()
{
    m_logger = TLogger::getInstance();
    m_emulatorRunning = true;
    m_cpu = new TCpu(this);
}

TChip8::~TChip8() {

}

void TChip8::init(string rom_path) {

    for(auto i = 0; i < SCREEN_HEIGHT; i++)
        for(auto j = 0; j < SCREEN_WIDTH; j++)
            m_screen[i][j] = 0;

    //clear ram
    for (auto i = 0; i < TOTAL_RAM; i++)
        m_ram[i] = 0;

    // load fonts
    for (auto i = 0; i < FONTSET_SIZE; i++)
        m_ram[i] = FONTSET[i];
    
    m_delay_timer = 0;
    m_sound_timer = 0;

    for (auto i = 0; i < NUM_KEYS; i++)
        m_keys[i] = 0;
    
    m_key_pressed = false;

    m_cpu->init();

    m_loader = new TRomLoader();
    m_loader->loadRom(rom_path, m_ram+PROGRAM_START_ADDR);
    delete m_loader;
        
}

void TChip8::run() {
    while(m_emulatorRunning) {
        m_cpu->fetch();
        m_cpu->decode();
        m_cpu->execute();
    }
}

void TChip8::deinit() {
    m_cpu->deinit();
}