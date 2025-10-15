#include <bitset>
#include <iostream>

#include "../Emulator/Commands.h"
#include "../Emulator/Emulator.h"

class SecondTask
{
public:
    static unsigned int* BinaryProgram()
    {
        auto *prog = new unsigned int[15];
        prog[0] = (0 << 28) + (0 <<  9) + (0 << 6);
        prog[1] = (3 << 28) + (0 << 9) + (0 << 6) + (0 << 3) + 0;
        prog[2] = (0 << 28) + (0 << 9) + (1 << 6) + (0 << 3) + 0;
        prog[3] = (5 << 28) + (0 << 9) + (2 << 6) + (0 << 3) + 0;
        prog[4] = (0 << 28) + (0 << 9) + (3 << 6) + (0 << 3) + 0;
        prog[5] = (0 << 28) + (0 << 9) + (4 << 6) + (0 << 3) + 0;
        prog[6] = (2 << 28) + (1 << 9) + (1 << 6) + (1 << 3) + 0;
        prog[7] = (2 << 28) + (1 << 9) + (2 << 6) + (2 << 3) + 0;
        prog[8] = (3 << 28) + (0 << 9) + (5 << 6) + (1 << 3) + 0;
        prog[9] = (3 << 28) + (0 << 9) + (6 << 6) + (2 << 3) + 0;
        prog[10] = (7 << 28) + (0 << 9) + (6 << 6) + (5 << 3) + 6;
        prog[11] = (6 << 28) + (0 << 9) + (4 << 6) + (4 << 3) + 5;
        prog[12] = (6 << 28) + (0 << 9) + (3 << 6) + (3 << 3) + 6;
        prog[13] = (4 << 28) + (6 << 9) + (0 << 6) + (1 << 3) + 0;
        prog[14] = (8 << 28);
        return prog;
    }
    static unsigned short* BinaryData()
    {
        auto *data = new unsigned short[13];
        data[0] = 6;


        data[1] = 65000;
        data[2] = 2;
        data[3] = 3;
        data[4] = 4;
        data[5] = 5;
        data[6] = 6;

        data[7] = 65000;
        data[8] = 8;
        data[9] = 9;
        data[10] = 10;
        data[11] = 11;
        data[12] = 12;
        return data;
    }

    static void RunInConsole()
    {
        auto emulator = Emulator();
        const auto prog = BinaryProgram();
        emulator.loadProgram(prog, 15);
        emulator.loadData(BinaryData(), 13);

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
                unsigned int result = 0;
                result += emulator.getRegister(4);
                result = result << 16;
                result += emulator.getRegister(3);
                std::cout << "result=" << result << std::endl;
            }
        }
    }
};
