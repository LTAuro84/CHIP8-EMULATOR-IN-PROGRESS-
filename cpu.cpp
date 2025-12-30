#include <cstdlib>
#include <ctime>

#include "cpu.h"
#include "logger.h"

TCpu::TCpu(TChip8* system) {
    chip8_system = system;
    m_logger = TLogger::getInstance();
}

TCpu::~TCpu() {

}

void TCpu::init() {
    program_counter = PC_START;
    current_opcode = 0;
    stack_pointer = 0;
    index_register = 0;
    instruction = 0;

    for (auto i = 0; i < NUM_V_REGISTERS; i++)
        data_registers[i] = 0;
}

void TCpu::fetch() {
    current_opcode = ((uint16_t)chip8_system->m_ram[program_counter] << 8) | chip8_system->m_ram[program_counter+1];
    program_counter += 2;
}

void TCpu::decode() {
    instruction = current_opcode >> 12;
}

void TCpu::execute() {
    m_logger->log("INST " + std::to_string(instruction), ELogLevel::DEBUG);

    switch (instruction)
    {

        case 0x0:
        case 0x1: 
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF: m_logger->log("Instruction Opcode Not Implemented", ELogLevel::ERROR); exit(1); break;
    }
}

void TCpu::deinit() {
    
}