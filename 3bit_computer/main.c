#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_INSTRUCTIONS 32

typedef enum {
    XDV = 0x0,
    YXL = 0x1,
    YST = 0x2,
    JNZ = 0x3,
    YXZ = 0x4,
    OUT = 0x5,
    YDV = 0x6,
    ZDV = 0x7,
} Opcode;

typedef struct {
    int8_t instructions[MAX_INSTRUCTIONS];
    int length;
} Program;

Program* create_program_1() {
    Program* program = (Program*)malloc(sizeof(Program));
    program->length = 6;
    program->instructions[0] = 0x0;
    program->instructions[1] = 0x1;
    program->instructions[2] = 0x5;
    program->instructions[3] = 0x4;
    program->instructions[4] = 0x3;
    program->instructions[5] = 0x0;
    return program;
}

Program* create_program_2() {
    Program* program = (Program*)malloc(sizeof(Program));
    program->length = 6;
    program->instructions[0] = 0x0;
    program->instructions[1] = 0x3;
    program->instructions[2] = 0x5;
    program->instructions[3] = 0x4;
    program->instructions[4] = 0x3;
    program->instructions[5] = 0x0;
    return program;
}


typedef struct {
    int64_t register_a;
    int64_t register_b;
    int64_t register_c;
    int instruction_pointer;
    Program* program;
}VirtualMachine;



void reset_VirtualMachine(VirtualMachine* vm) {
    vm->register_a = 0;
    vm->register_b = 0;
    vm->register_c = 0;
    vm->instruction_pointer = 0;
    vm->program = NULL;
}
void load_program(VirtualMachine* vm, Program* program) {
    reset_VirtualMachine(vm);
    vm->program = program;
}

void set_virtual_machine_to_stage1(VirtualMachine* vm) {
    Program* program = create_program_1();
    load_program(vm, program);
    vm->register_a = 3729;
}

void set_virtual_machine_to_stage2(VirtualMachine* vm) {
    Program* program = create_program_2();
    load_program(vm, program);
    vm->register_a = 8642024;
}

int64_t get_combo_value(VirtualMachine* vm,int8_t operand) {
    switch (operand) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return vm->register_a;
        case 5: return vm->register_b;
        case 6: return vm->register_c;
        default: return -1;
    }
}

void single_cycle(VirtualMachine* vm) {


    int instruction_pointer = vm->instruction_pointer;
    int instruction = vm->program->instructions[instruction_pointer];
    int operand = vm->program->instructions[instruction_pointer+1];
    int64_t combo = get_combo_value(vm,operand);
    int64_t placeholder;
    bool increment_pc = true;
    switch (instruction) {
        case 0:
            placeholder = vm->register_a;
            vm->register_a = placeholder >> combo;
            increment_pc  = true;
            break;
        case 1:
            vm->register_b = vm->register_b^operand;
            increment_pc  = true;
            break;
        case 2:
            vm->register_b = combo % 8;
            increment_pc  = true;
            break;
        case 3:
            if (vm->register_a!=0) {
                vm->instruction_pointer = operand;
                increment_pc = false;
            }
            break;
        case 4:
            vm->register_b = vm->register_b^vm->register_c;
            increment_pc = true;
            break;
        case 5:
            placeholder = combo % 8;
            increment_pc = true;
            printf("%lld,",placeholder);
            break;
        case 6:
            placeholder = vm->register_a;
            vm->register_b = placeholder >> combo;
            increment_pc  = true;
            break;
        case 7:
            placeholder = vm->register_a;
            vm->register_c = placeholder >> combo;
            increment_pc  = true;
            break;
    }
    if (increment_pc) {
        vm->instruction_pointer+=2;
    }
};



int main(void) {
    VirtualMachine vm;

    set_virtual_machine_to_stage1(&vm);

    while (vm.instruction_pointer < vm.program->length) {
        single_cycle(&vm);
    }

    free(vm.program);
    return 0;


}