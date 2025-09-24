#ifndef EMULATOR_LIBRARY_H
#define EMULATOR_LIBRARY_H
#include <cstdint>
#include <string>

class Emulator {
public:
    static const int MEM_SIZE = 64;
    static const int REG_SIZE = 4;

private:
    uint32_t cmem[MEM_SIZE];
    uint32_t dmem[MEM_SIZE];
    uint32_t registers[REG_SIZE];
    uint32_t pc;
    uint32_t cmd;
    uint32_t flags;

public:
    Emulator();

    // loads data to memory
    void loadData(const uint32_t data[]);

    // loads program to memory as binary code
    void loadProgram(const uint32_t program[]);

    // loads program to memory as assembler commands
    void loadProgram(const std::string program[]);

    // returns register by id
    uint32_t getRegister(int id) const;

    // returns program counter
    uint32_t getPC() const;

    // returns current command
    uint32_t getCMD() const;

    // starts infinite loop
    void run();

    // runs current step
    void step();
};


#endif // EMULATOR_LIBRARY_H