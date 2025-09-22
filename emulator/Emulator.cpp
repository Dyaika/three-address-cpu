#include "Emulator.h"
#define ADD 1
#define SUB 2
#define INC 3
#define DEC 4
#define AND 5
#define OR 6
#define XOR 7

Emulator::Emulator(): pc(0), cmd(0), flags(0) {
    // init memory here
}

void Emulator::loadData(const uint32_t data[]) {
    for (int i = 0; i < MEM_SIZE; ++i) {
        dmem[i] = data[i];
    }
}

void Emulator::loadProgram(const uint32_t program[]) {
    for (int i = 0; i < MEM_SIZE; ++i) {
        cmem[i] = program[i];
    }
}

uint32_t Emulator::getRegister(int id) const {
    return registers[id];
}

uint32_t Emulator::getPC() const {
    return pc;
}

uint32_t Emulator::getCMD() const {
    return cmd;
}

uint32_t Emulator::getFlags() const {
    return flags;
}

void Emulator::run() {
    while (1) {
        step();
    }
}

void Emulator::step() {
    cmd = cmem[pc];

    // 31-28 cmdtype
    // 27-12 literal
    // 11-8 dest
    // 7-4 op1
    // 3-0 op2
    const uint32_t cmd_type = cmd & (0xf << 28) >> 28;
    const uint32_t literal = cmd & (0xffff << 12) >> 12;
    const uint32_t dest = cmd & (0xf << 8) >> 8;
    const uint32_t op1 = cmd & (0xf << 4) >> 4;
    const uint32_t op2 = cmd & 0xf;

    switch (cmd_type) {
        case ADD:
            registers[dest] = registers[op1] + registers[op2];
            pc++;
            break;
        case SUB:
            registers[dest] = registers[op1] - registers[op2];
            pc++;
            break;
        case INC:
            registers[dest] = ++registers[dest];
            pc++;
            break;
        case DEC:
            registers[dest] = --registers[dest];
            pc++;
            break;
        case AND:
            registers[dest] = registers[op1] & registers[op2];
            pc++;
            break;
        case OR:
            registers[dest] = registers[op1] | registers[op2];
            pc++;
            break;
        case XOR:
            registers[dest] = registers[op1] ^ registers[op2];
            pc++;
            break;
    }
    // magic here
    pc++;
}
