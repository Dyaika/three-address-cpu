#include <bitset>
#include <iostream>

#include "Emulator.h"

int main() {
    auto emulator = Emulator();
    unsigned int prog[28];
    prog[0] = (0 << 29) + (5 << 6) + (0 << 4);               // n в R0
    prog[1] = (0 << 29) + (0 << 6) + (1 << 4);               // i = 0
    prog[2] = (1 << 29) + (1 << 4) + (0 << 2);               // n в память

    prog[3] = (2 << 29) + (1 << 6) + (1 << 4) + (1 << 2);    // i++
    prog[4] = (0 << 29) + (6 << 6) + (0 << 4);               // 6 в R0
    prog[5] = (1 << 29) + (1 << 4) + (0 << 2);               // R0 в память
    prog[6] = (2 << 29) + (1 << 6) + (1 << 4) + (1 << 2);    // i++
    prog[7] = (0 << 29) + (2 << 6) + (0 << 4);               // 2 в R0
    prog[8] = (1 << 29) + (1 << 4) + (0 << 2);               // R0 в память
    prog[9] = (2 << 29) + (1 << 6) + (1 << 4) + (1 << 2);    // i++
    prog[10] = (0 << 29) + (1 << 6) + (0 << 4);              // 1 в R0
    prog[11] = (1 << 29) + (1 << 4) + (0 << 2);              // R0 в память
    prog[12] = (2 << 29) + (1 << 6) + (1 << 4) + (1 << 2);   // i++
    prog[13] = (0 << 29) + (8 << 6) + (0 << 4);              // 8 в R0
    prog[14] = (1 << 29) + (1 << 4) + (0 << 2);              // R0 в память
    prog[15] = (2 << 29) + (1 << 6) + (1 << 4) + (1 << 2);   // i++
    prog[16] = (0 << 29) + (3 << 6) + (0 << 4);              // 3 в R0
    prog[17] = (1 << 29) + (1 << 4) + (0 << 2);              // R0 в память

    prog[18] = (0 << 29) + (0 << 6) + (0 << 4);              // id = 0
    prog[19] = (3 << 29) + (1 << 4) + (0 << 2);              // n
    prog[20] = (0 << 29) + (1 << 6) + (2 << 4);              // firstId = 1
    prog[21] = (3 << 29) + (3 << 4) + (2 << 2);              // первый элемент в макс
    // l1(22):
    prog[22] = (2 << 29) + (1 << 6) + (0 << 4) + (0 << 2);   // id++
    prog[23] = (3 << 29) + (2 << 4) + (0 << 2);              // очередной элемент
    prog[24] = (4 << 29) + (26 << 6) + (2 << 2) + 3;         // элемент < макс => прыжок на l2
    prog[25] = (5 << 29) + (3 << 4) + (2 << 2);              // элемент в макс
    // l2(26):
    prog[26] = (4 << 29) + (22 << 6) + (0 << 2) + 1;         // id < n => прыжок на l1
    prog[27] = (6 << 29);                                    // конец
    emulator.loadProgram(prog);

    while (std::cin.get()) {
        std::cout << "pc: " << emulator.getPC() << std::endl;
        std::cout << "cmd: " << std::bitset<32>(emulator.getCMD()) << std::endl;
        for (auto i = 0; i < Emulator::REG_SIZE; i++) {
            std::cout << "R" << i << "\t";
        }
        std::cout << std::endl;
        for (auto i = 0; i < Emulator::REG_SIZE; i++) {
            std::cout << emulator.getRegister(i) << "\t";
        }
        std::cout << std::endl;
        emulator.step();
        if (emulator.getCMD() >> 29 == 6) {

            std::cout << std::endl << "--------END OF PROGRAM--------" << std::endl;
            std::cout << "max=" << emulator.getRegister(3) << std::endl;
            return 0;
        }
    }
    return 0;
}
