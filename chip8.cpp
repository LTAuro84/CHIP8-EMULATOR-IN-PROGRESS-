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
    
}