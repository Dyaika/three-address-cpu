#include "Emulator.h"
#include "Commands.h"

Emulator::Emulator(): pc(0), cmd(0), overflowFlag(false) {
    // init memory here
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }
    for (int i = 0; i < MEM_SIZE; i++) {
        dmem[i] = 0;
        cmem[i] = 0;
    }
}

void Emulator::loadData(const unsigned short data[], int n) {
    for (int i = 0; i < n; ++i) {
        dmem[i] = data[i];
    }
}

void Emulator::loadProgram(const unsigned int program[], int n) {
    for (int i = 0; i < MEM_SIZE; ++i) {
        cmem[i] = program[i];
    }
}

unsigned short Emulator::getRegister(const int id) const {
    return registers[id];
}

unsigned short Emulator::getPC() const {
    return pc;
}

unsigned int Emulator::getCMD() const {
    return cmem[pc];
}

bool Emulator::getOverflowFlag() const
{
    return overflowFlag;
}

void Emulator::run() {
    while (true) {
        step();
    }
}

void Emulator::step() {
    cmd = cmem[pc];

    // 31-28 cmdtype (4 bit)
    // empty 3 bits
    // 24-9 literal  (16 bit)
    // 8-6 dest      (3 bit)
    // 5-3 op1       (3 bit)
    // 2-0 op2       (3 bit)
    const unsigned short cmd_type = cmd >> 28 & 0xF;
    const unsigned short literal = cmd  >> 9 & 0xFFFF;
    const unsigned short dest = cmd >> 6 & 0x7;
    const unsigned short op1 = cmd >> 3 & 0x7;
    const unsigned short op2 = cmd & 0x7;
    unsigned int multiplication;


    switch (cmd_type)
    {
    case Commands::LTR:
        registers[dest] = literal;
        pc++;
        break;
    case Commands::RTM:
        dmem[registers[dest]] = registers[op1];
        pc++;
        break;
    case Commands::ADDL:
        registers[dest] = registers[op1] + literal;
        pc++;
        break;
    case Commands::MTR:
        registers[dest] = dmem[registers[op1]];
        pc++;
        break;
    case Commands::JIL:
        if (registers[op1] < registers[op2])
        {
            pc = literal;
        }
        else
        {
            pc++;
        }
        break;
    case Commands::RTR:
        registers[dest] = registers[op1];
        pc++;
        break;
    case Commands::ADD:
        registers[dest] = registers[op1] + registers[op2];
        pc++;
        break;
    case Commands::MUL:
        multiplication = registers[op1] * registers[op2];
        registers[dest] = multiplication & 0xFFFF;
        registers[op1] = multiplication >> 16;
        pc++;
        break;
    case Commands::END:
        break;
    default:
        pc++;
        break;
    }
}
