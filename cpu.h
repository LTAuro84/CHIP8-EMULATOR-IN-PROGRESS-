#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>

#include "chip8.h"
#include "logger.h"

#define NUM_V_REGISTERS 16
#define PC_START 0X200

class TCpu {

    uint8_t data_registers[NUM_V_REGISTERS]; // 8 bit register
    uint16_t index_register; // memory address pointer
    uint16_t program_counter; 
    uint16_t stack_pointer;
    
    uint16_t current_opcode;
    uint16_t instruction;

    TChip8* chip8_system;

    void clear_screen();
    void return_from_subroutine();
    void jump_to_nnn();
    void calls_at_nnn();
    void skip_instruction();
    void skip_instruction2();
    void skip_instruction3();
    void register_set();
    void add_reg_imm();
    void move_vy_to_vx();
    void or_vx_vy();
    void and_vx_vy();
    void xor_vx_vy();
    void add_vx_vy();
    void sub_vx_vy();
    void shift_right_reg();
    void subtract_vx_vy();
    void shift_left_reg();
    void skip_next_instruction();
    void set_index_reg();
    void jump_to_v0();
    void generate_random_number();
    void drawing_sprite();
    void skip_inst_if_vx_pressed();
    void skip_inst_if_vx_isnt_pressed();
    void reg_delay_timer();
    void wait_for_key_press();
    void delay_timer_with_reg();
    void sound_timer_with_reg();
    void vx_to_ireg();
    void load_sprite_from_vx();
    void store_binary_code_decimal_representation();

    std::shared_ptr<TLogger> m_logger;

public:
    TCpu(TChip8* system);
    ~TCpu();
    void init();
    void fetch();
    void decode();
    void execute();
    void deinit();
};

#endif
