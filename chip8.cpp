#include "cpu.h"
#include "chip8.h"
#include "display.h"
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
    m_display = nullptr;
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

    m_display->init();
        
}

void TChip8::run() {

    using clock = chrono::high_resolution_clock;
    clock::time_point start, end;
    const chrono::milliseconds desired_cycle_time(1);

    int display_update_delay_time = 0;

    while(m_emulatorRunning) {

        start = clock::now();

        m_cpu->fetch();
        m_cpu->decode();
        m_cpu->execute();

        if (display_update_delay_time >= 20) {
            display_update_delay_time = 0;
            m_display->draw(m_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            m_display->update();

            if (m_delay_timer > 0) {
                m_delay_timer--;
            }

            if (m_sound_timer > 0) {
                m_sound_timer--;
            }
        }

        end = clock::now();

        chrono::duration<double, micro> loop_time = end - start;
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end - start);
        auto sleep_time = desired_cycle_time - elapsed_time;
        if (sleep_time.count() > 0) {
            this_thread::sleep_for(sleep_time);
        }

        display_update_delay_time++;
        
    }
}

void TChip8::deinit() {
    m_cpu->deinit();

    m_display->deinit();
}

void TChip8::setDisplay(TDisplay* display) {
    m_display = display;
}