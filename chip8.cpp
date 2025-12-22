#include "chip8.h"
#include "logger.h"
using namespace std;

TChip8::TChip8()
{
    m_logger = TLogger::getInstance();
    m_emulatorRunning = true;
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
        
}

void TChip8::run() {

}

void TChip8::deinit() {

}