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

// CHIP8 Instructions

//00E0 - CLS
//Clear the display
void TCpu::clear_screen() {
    for (int i = 0; i < SCREEN_HEIGHT; i++)
        for (int j = 0; j < SCREEN_WIDTH; j++)
            chip8_system->m_screen[i][j] = 0;
}

//00EE - RET
//Return from a subroutine
void TCpu::return_from_subroutine() {
    stack_pointer--;
    program_counter = chip8_system->m_stack[stack_pointer];
}

//1nnn - JP addr
//Jump to location nnn
void TCpu::jump_to_nnn() {
    program_counter = current_opcode & 0x0FFF;
}

//2nnn - CALL addr
//Call subroutine at nnn
void TCpu::calls_at_nnn() {
    uint16_t nnn = current_opcode & 0x0FFF;

    chip8_system->m_stack[stack_pointer] = program_counter;
    stack_pointer++;
    program_counter = nnn;
}

//3xkk - SE Vx, byte
//Skip next instruction if Vx = kk
void TCpu::skip_instruction() {
    uint8_t value = current_opcode & 0xFF;
    uint8_t reg = (current_opcode >> 8) & 0x0F;

    if(data_registers[reg] == value) {
        program_counter += 2;
    }
}

//4xkk - SNE Vx, byte
//Skip next instruction if Vx != kk
void TCpu::skip_instruction2() {
    uint8_t value = current_opcode & 0xFF;
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    
    if (data_registers[reg] != value) {
        program_counter += 2;
    }
}