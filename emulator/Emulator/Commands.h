#ifndef COMMANDS_H
#define COMMANDS_H
class Commands
{
public:
    static const int LTR = 0;
    static const int RTM = 1;
    static const int ADDL = 2;
    static const int MTR = 3;
    static const int JIL = 4;
    static const int RTR = 5;
    static const int ADD = 6;
    static const int MUL = 7;
    static const int END = 8;

    static int map(const std::string& cmd) {
        if (cmd == "LTR") return LTR;
        if (cmd == "RTM") return RTM;
        if (cmd == "ADDL") return ADDL;
        if (cmd == "MTR") return MTR;
        if (cmd == "JIL") return JIL;
        if (cmd == "RTR") return RTR;
        if (cmd == "ADD") return ADD;
        if (cmd == "MUL") return MUL;
        if (cmd == "END") return END;

        return -1;
    }
};

#endif //COMMANDS_H
