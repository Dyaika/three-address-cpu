#include "Emulator.h"
#define ADD 1
#define SUB 2

Emulator::Emulator(): pc(0), ir(0), flags(0) {
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

uint32_t Emulator::getIR() const {
    return ir;
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
    ir = cmem[pc];

    // 31-28 cmdtype
    // 27-12 literal
    // 11-8 dest
    // 7-4 op1
    // 3-0 op2
    const uint32_t cmd = ir & (0xf << 28) >> 28;
    const uint32_t literal = ir & (0xffff << 12) >> 12;
    const uint32_t dest = ir & (0xf << 8) >> 8;
    const uint32_t op1 = ir & (0xf << 4) >> 4;
    const uint32_t op2 = ir & 0xf;

    switch (cmd) {
        case ADD:
            registers[dest] = registers[op1] + registers[op2];
            pc++;
            break;
        case SUB:
            registers[dest] = registers[op1] - registers[op2];
            pc++;
            break;
    }
    // magic here
    pc++;
}
