#include <bitset>
#include <iostream>

#include "../Emulator/Commands.h"
#include "../Emulator/Emulator.h"

class FirstTask
{
public:
    static unsigned int* BinaryProgram()
    {
        auto *prog = new unsigned int[28];
        prog[0] = (0 << 28) + (5 <<  9) + (0 << 6); // n в R0
        prog[1] = (0 << 28) + (0 <<  9) + (1 << 6); // i = 0
        prog[2] = (1 << 28) + (1 << 6) + (0 << 3); // n в память

        prog[3] = (2 << 28) + (1 <<  9) + (1 << 6) + (1 << 3); // i++
        prog[4] = (0 << 28) + (6 <<  9) + (0 << 6); // 6 в R0
        prog[5] = (1 << 28) + (1 << 6) + (0 << 3); // R0 в память
        prog[6] = (2 << 28) + (1 <<  9) + (1 << 6) + (1 << 3); // i++
        prog[7] = (0 << 28) + (2 <<  9) + (0 << 6); // 2 в R0
        prog[8] = (1 << 28) + (1 << 6) + (0 << 3); // R0 в память
        prog[9] = (2 << 28) + (1 <<  9) + (1 << 6) + (1 << 3); // i++
        prog[10] = (0 << 28) + (1 <<  9) + (0 << 6); // 1 в R0
        prog[11] = (1 << 28) + (1 << 6) + (0 << 3); // R0 в память
        prog[12] = (2 << 28) + (1 <<  9) + (1 << 6) + (1 << 3); // i++
        prog[13] = (0 << 28) + (8 <<  9) + (0 << 6); // 8 в R0
        prog[14] = (1 << 28) + (1 << 6) + (0 << 3); // R0 в память
        prog[15] = (2 << 28) + (1 <<  9) + (1 << 6) + (1 << 3); // i++
        prog[16] = (0 << 28) + (3 <<  9) + (0 << 6); // 3 в R0
        prog[17] = (1 << 28) + (1 << 6) + (0 << 3); // R0 в память

        prog[18] = (0 << 28) + (0 <<  9) + (0 << 6); // id = 0
        prog[19] = (3 << 28) + (1 << 6) + (0 << 3); // n
        prog[20] = (0 << 28) + (1 <<  9) + (2 << 6); // firstId = 1
        prog[21] = (3 << 28) + (3 << 6) + (2 << 3); // первый элемент в макс
        // l1(22):
        prog[22] = (2 << 28) + (1 <<  9) + (0 << 6) + (0 << 3); // id++
        prog[23] = (3 << 28) + (2 << 6) + (0 << 3); // очередной элемент
        prog[24] = (4 << 28) + (26 <<  9) + (2 << 3) + 3; // элемент < макс => прыжок на l2
        prog[25] = (5 << 28) + (3 << 6) + (2 << 3); // элемент в макс
        // l2(26):
        prog[26] = (4 << 28) + (22 <<  9) + (0 << 3) + 1; // id < n => прыжок на l1
        prog[27] = (9 << 28); // конец
        return prog;
    }

    static void RunInConsole()
    {
        auto emulator = Emulator();
        const auto prog = BinaryProgram();
        emulator.loadProgram(prog, 28);

        while (std::cin.get())
        {
            std::cout << "pc: " << emulator.getPC() << std::endl;
            std::cout << "cmd: " << std::bitset<32>(emulator.getCMD()) << std::endl;
            for (auto i = 0; i < Emulator::REG_SIZE; i++)
            {
                std::cout << "R" << i << "\t";
            }
            std::cout << std::endl;
            for (auto i = 0; i < Emulator::REG_SIZE; i++)
            {
                std::cout << emulator.getRegister(i) << "\t";
            }
            std::cout << std::endl;
            emulator.step();
            if (emulator.getCMD() >> 28 == Commands::END)
            {
                std::cout << std::endl << "--------END OF PROGRAM--------" << std::endl;
                std::cout << "max=" << emulator.getRegister(3) << std::endl;
            }
        }
    }
};
