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
    int64_t register_x;
    int64_t register_y;
    int64_t register_z;
    int instruction_pointer;
    Program* program;

}VirtualMachine;



void reset_VirtualMachine(VirtualMachine* vm) {
    vm->register_x = 0;
    vm->register_y = 0;
    vm->register_z = 0;
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
    vm->register_x = 3729;
}

void set_virtual_machine_to_stage2(VirtualMachine* vm) {
    Program* program = create_program_2();
    load_program(vm, program);
    vm->register_x = 8642024;
}

void single_cycle(VirtualMachine* vm) {

};



int main(void) {
    printf("Hello, World!\n");
    return 0;
}