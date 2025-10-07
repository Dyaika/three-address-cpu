#ifndef EMULATOR_LIBRARY_H
#define EMULATOR_LIBRARY_H
#include <string>

class Emulator {
public:
    static const int MEM_SIZE = 64;
    static const int REG_SIZE = 8;

private:
    unsigned int cmem[MEM_SIZE];
    unsigned short dmem[MEM_SIZE];
    unsigned short registers[REG_SIZE];
    unsigned short pc;
    unsigned int cmd;
    bool overflowFlag;

public:
    Emulator();

    // loads data to memory
    void loadData(const unsigned short data[], int n);

    // loads program to memory as binary code
    void loadProgram(const unsigned int program[], int n);

    // loads program to memory as assembler commands TODO: implement
    void loadProgram(const std::string program[], int n);

    // returns register by id
    unsigned short getRegister(int id) const;

    // returns program counter
    unsigned short getPC() const;

    // returns current command
    unsigned int getCMD() const;

    // was overflow on the last operation
    bool getOverflowFlag() const;

    // starts infinite loop
    void run();

    // runs current step
    void step();
};


#endif // EMULATOR_LIBRARY_H