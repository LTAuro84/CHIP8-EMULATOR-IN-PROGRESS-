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

//kk = 8 bit number
//Vx = refers to the registers

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

//5xy0 - SE Vx, byte
//Skip next instruction if Vx = Vy
void TCpu::skip_instruction3() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    if (data_registers[reg_x] == data_registers[reg_y]) {
        program_counter += 2;
    }
}

//6xkk - Set register to constant value
//Vx = kk

void TCpu::register_set() {
    uint8_t value = current_opcode & 0xFF;
    uint8_t reg = (current_opcode >> 8) & 0x0F;

    data_registers[reg] = value;
}

//7xkk - Set Vx = Vx + kk
void TCpu::add_reg_imm() {
    uint8_t value = current_opcode & 0xFF;
    uint8_t reg = (current_opcode >> 8) & 0x0F;

    data_registers[reg] += value;
}


//8xy0 - Load Vx with Vy
void TCpu::move_vy_to_vx() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    data_registers[reg_x] == data_registers[reg_y];
}

//8xy1 - OR of Vx with Vy
void TCpu::or_vx_vy() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    data_registers[reg_x] |= data_registers[reg_y];
}

//8xy2 - AND of Vx with Vy
void TCpu::and_vx_vy() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    data_registers[reg_x] &= data_registers[reg_y];
}

//8xy3 - XOR of Vx with Vy
void TCpu::xor_vx_vy() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    data_registers[reg_x] ^= data_registers[reg_y];
}

//8xy4 - ADD Vx with Vy
void TCpu::add_vx_vy() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;
    uint16_t add = data_registers[reg_x] + data_registers[reg_y];

    if (add > 0xFF) {
        data_registers[0xF] = 1;
    }
    else {
        data_registers[0xF] = 0;
    }

    data_registers[reg_x] = add & 0xFF;
}

//8xy5 - Substract Vy from Vx
void TCpu::sub_vx_vy() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    if (data_registers[reg_x] > data_registers[reg_y]) {
            data_registers[0xF] = 1;
    }

    else {
        data_registers[0xF] = 0;
    }

    data_registers[reg_x] -= data_registers[reg_y];
}

//8xy6 - Vx divided by 2
void TCpu::shift_right_reg() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;

    if(data_registers[reg] % 2 == 1) {
        data_registers[0xF] = 1;
    }

    else {
        data_registers[0xF] = 0;
    }

    data_registers[reg] >>= 1;
}

//8xy7 - Subtract Vx from fy
void TCpu::subtract_vx_vy() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    if (data_registers[reg_y] > data_registers[reg_x]) {
        data_registers[0xF] = 1;
    }

    else {
        data_registers[0xF] = 0;
    }

    data_registers[reg_x] = data_registers[reg_y] - data_registers[reg_x];             
}

//8xye - Vx multiplied by 2
void TCpu::shift_left_reg() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;

    if (data_registers[reg] & 0x80 == 1) {
        data_registers[0xF] = 1;
    }
    else {
        data_registers[0xF] = 0;
    }

    data_registers[reg] <<= 1;
}

//9xy0 - If Vx != Vy, skip next instruction
void TCpu::skip_next_instruction() {
    uint8_t reg_x = (current_opcode >> 8) & 0x0F;
    uint8_t reg_y = (current_opcode >> 4) & 0x0F;

    if (data_registers[reg_x] != data_registers[reg_y]) {
        program_counter += 2;
    }
} 

//ANNN - Load index register
void TCpu::set_index_reg() {
    index_register = current_opcode & 0x0FFF;
}

//BNNN - Jump to NNN+V0
void TCpu::jump_to_v0() {
    uint16_t nnn = current_opcode & 0x0FFF;
    program_counter = nnn + data_registers[0];
}

//CXKK - Generate a random number
void TCpu::generate_random_number() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    uint8_t kk = current_opcode & 0xFF;
    uint8_t random_number = rand() % 256;

    data_registers[reg] = random_number & kk;
}

//DXYN - Draw sprite
void TCpu::drawing_sprite() {
    uint8_t v_reg_x = (current_opcode & 0x0F00) >> 8;
    uint8_t v_reg_y = (current_opcode & 0x00F0) >> 4;
    uint8_t sprite_height = current_opcode & 0x000F;
    uint8_t x = data_registers[v_reg_x];
    uint8_t y = data_registers[v_reg_y];

    data_registers[0xF] = 0;
    for (int y_coordinate = 0; y_coordinate < sprite_height; y_coordinate++) {
        uint8_t pixel = chip8_system->m_ram[index_register + y_coordinate];
        for (int x_coordinate = 0; x_coordinate < 8; x_coordinate++) {
            
            if((pixel & (0x80 >> x_coordinate)) != 0) {
                
                if (chip8_system->m_screen[y + y_coordinate][x + x_coordinate] == 1) {
                    data_registers[0xF] = 1;

                    chip8_system->m_screen[y + y_coordinate][x + x_coordinate] ^= 0x1;
                }
            }
        }
    }
}

//EX93 - Skip instruction if Vx key is pressed
void TCpu::skip_inst_if_vx_pressed() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    uint8_t val = data_registers[reg];

    if (chip8_system->m_keys[val] != 0) {
        program_counter += 2;
    }
}

//EXA1 - Skip instruction if Vx key isn't pressed
void TCpu::skip_inst_if_vx_isnt_pressed() {
       uint8_t reg = (current_opcode >> 8) & 0x0F;
    uint8_t val = data_registers[reg];

    if (chip8_system->m_keys[val] == 0) {
        program_counter += 2;
    }
}

//FX07 - Register with delay timer
void TCpu::reg_delay_timer() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    data_registers[reg] = chip8_system->m_delay_timer;
}

//FX0A - Waits for key press
void TCpu::wait_for_key_press() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    bool key_pressed = false;

    for (int i = 0; i < NUM_KEYS; i++) {
        if (chip8_system->m_keys[i] != 0) {
            data_registers[reg] = i;
            key_pressed = true;
        }
    }

    if (!key_pressed) {
        program_counter -= 2;
    }
}

//FX15 - Delay timer with register
void TCpu::delay_timer_with_reg() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    chip8_system->m_delay_timer = data_registers[reg];
}

//FX18 - Sound timer with register
void TCpu::sound_timer_with_reg() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    chip8_system->m_sound_timer = data_registers[reg];
}

//FX1E - Vx to I register
void TCpu::vx_to_ireg() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    index_register += data_registers[reg];
}

//FX29 - I register with sprite location
void TCpu::load_sprite_from_vx() {
    uint8_t reg = (current_opcode >> 8) & 0x0F;
    index_register = data_registers[reg] * 0x5;
}