#ifndef EMULATOR_LIBRARY_H
#define EMULATOR_LIBRARY_H
#include <vector>
#include <array>
#include <cstdint>

class Emulator {
public:
    static const int MEM_SIZE = 1024;
    static const int NUM_REGISTERS = 16;

private:
    uint32_t cmem[MEM_SIZE];  // Память команд
    uint32_t dmem[MEM_SIZE];  // Память данных
    uint32_t registers[NUM_REGISTERS];
    uint32_t pc;
    uint32_t ir;
    uint32_t flags;

public:
    Emulator();

    void loadData(const uint32_t data[]);

    void loadProgram(const uint32_t program[]);

    // returns register by id
    uint32_t getRegister(int id) const;

    // returns program counter
    uint32_t getPC() const;

    // returns ?? register
    uint32_t getIR() const;

    // returns flags
    uint32_t getFlags() const;

    // starts infinite loop
    void run();

    // runs current step
    void step();
};


#endif // EMULATOR_LIBRARY_H