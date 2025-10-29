#include "Emulator.h"

#include <unordered_map>
#include <sstream>
#include "Commands.h"

Emulator::Emulator(): pc(0) {
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

void Emulator::loadProgram(const std::string program[], int n) {
    std::unordered_map<std::string, int> label_dict;
    int label_count = 0;
    for (int i = 0; i < n; i++) {
        if (!program[i].empty() && program[i].back() == ':') {
            std::string label = program[i].substr(0, program[i].size() - 1);
            label_dict[label] = i - label_count;
            label_count++;
        }
    }
    auto *prog = new unsigned int[n - label_count];
    int id = 0;
    for (int i = 0; i < n; i++) {
        if (!program[i].empty() && program[i].back() != ':') {
            std::string cleaned;
            // Убираем символы ',', '[', ']', 'R'
            for (char ch : program[i]) {
                if (ch != ',' && ch != '[' && ch != ']') {
                    cleaned += ch;
                }
            }

            std::string parts[5];
            std::istringstream iss(cleaned);
            std::string part;
            int partId = 0;
            while (iss >> part) {
                parts[partId] = part;
                partId++;
            }
            int cmd_type = Commands::map(parts[0]);
            unsigned short literal = 0;
            unsigned short dest = 0;
            unsigned short op1 = 0;
            unsigned short op2 = 0;

            switch (cmd_type)
            {
                case Commands::LTR:
                    literal = stoi(parts[1]);
                    dest = stoi(parts[2].substr(1));
                    break;
                case Commands::RTM:
                    dest = stoi(parts[1].substr(1));
                    op1 = stoi(parts[2].substr(1));
                    break;
                case Commands::ADDL:
                    literal = stoi(parts[1]);
                    dest = stoi(parts[2].substr(1));
                    op1 = stoi(parts[3].substr(1));
                    break;
                case Commands::MTR:
                    dest = stoi(parts[1].substr(1));
                    op1 = stoi(parts[2].substr(1));
                    break;
                case Commands::JIL:
                    literal = label_dict[parts[1]];
                    op1 = stoi(parts[2].substr(1));
                    op2 = stoi(parts[3].substr(1));
                    break;
                case Commands::RTR:
                    dest = stoi(parts[1].substr(1));
                    op1 = stoi(parts[2].substr(1));
                    break;
                case Commands::ADD:
                    dest = stoi(parts[1].substr(1));
                    op1 = stoi(parts[2].substr(1));
                    op2 = stoi(parts[3].substr(1));
                    break;
                case Commands::MUL:
                    dest = stoi(parts[1].substr(1));
                    op1 = stoi(parts[2].substr(1));
                    op2 = stoi(parts[3].substr(1));
                    break;
                case Commands::END:
                    break;
                default:
                    cmd_type = Commands::END;
                    break;
            }
            const unsigned int command = (cmd_type << 28) + (literal << 9) + (dest << 6) + (op1 << 3) + op2;
            prog[id] = command;
            id++;
        }
    }
    loadProgram(prog, id);
    delete[] prog;
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

void Emulator::run() {
    while ((getCMD() >> 28 & 0xF) != Commands::END) {
        step();
    }
}

void Emulator::step() {
    unsigned int cmd = cmem[pc];

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
