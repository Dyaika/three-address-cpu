#include "Emulator.h"

#define LTR 0
#define RTM 1
#define ADDL 2
#define MTR 3
#define JIL 4
#define RTR 5
#define END 6

Emulator::Emulator(): pc(0), cmd(0), flags(0) {
    // init memory here
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }
    for (int i = 0; i < MEM_SIZE; i++) {
        dmem[i] = 0;
        cmem[i] = 0;
    }
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
    return cmem[pc];
}

void Emulator::run() {
    while (1) {
        step();
    }
}

void Emulator::step() {
    cmd = cmem[pc];

    // 31-29 cmdtype (3 bit)
    // 28-6 literal  (23 bit)
    // 5-4 dest      (2 bit)
    // 3-2 op1       (2 bit)
    // 1-0 op2       (2 bit)
    const uint32_t cmd_type = cmd >> 29;
    const uint32_t literal = cmd << 3 >> 9;
    const uint32_t dest = cmd << 26 >> 30;
    const uint32_t op1 = cmd << 28 >> 30;
    const uint32_t op2 = cmd << 30 >> 30;

    switch (cmd_type) {
        case LTR:
            registers[dest] = literal;
            pc++;
            break;
        case RTM:
            dmem[registers[dest]] = registers[op1];
            pc++;
            break;
        case ADDL:
            registers[dest] = registers[op1] + literal;
            pc++;
            break;
        case MTR:
            registers[dest] = dmem[registers[op1]];
            pc++;
            break;
        case JIL:
            if (registers[op1] < registers[op2]) {
                pc = literal;
            } else {
                pc++;
            }
            break;
        case RTR:
            registers[dest] = registers[op1];
            pc++;
            break;
        case END:
            break;
        default:
            pc++;
            break;
    }
}
