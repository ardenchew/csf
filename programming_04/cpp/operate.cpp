#include <stdio.h>
#include <ctype.h>

#include <string>
#include <map>

#include "error.h"

int get_byte(std::string opcode, long int arg, bool empty) {

    std::map<std::string, std::pair<unsigned char, bool> > op_dict;
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("HLT", std::pair<unsigned char, bool>(0,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("DAT", std::pair<unsigned char, bool>(0,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("EXT", std::pair<unsigned char, bool>(0,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("LDA", std::pair<unsigned char, bool>(16,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("LDI", std::pair<unsigned char, bool>(32,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("STA", std::pair<unsigned char, bool>(48,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("STI", std::pair<unsigned char, bool>(64,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("ADD", std::pair<unsigned char, bool>(80,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("SUB", std::pair<unsigned char, bool>(96,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("JMP", std::pair<unsigned char, bool>(112,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("JMZ", std::pair<unsigned char, bool>(128,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("AND", std::pair<unsigned char, bool>(144,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("IOR", std::pair<unsigned char, bool>(160,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("XOR", std::pair<unsigned char, bool>(176,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("ADL", std::pair<unsigned char, bool>(192,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("ADC", std::pair<unsigned char, bool>(208,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("SBB", std::pair<unsigned char, bool>(224,0)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("NEG", std::pair<unsigned char, bool>(240,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("COM", std::pair<unsigned char, bool>(241,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("CLR", std::pair<unsigned char, bool>(242,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("SET", std::pair<unsigned char, bool>(243,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("RTL", std::pair<unsigned char, bool>(244,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("RTR", std::pair<unsigned char, bool>(245,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("LSL", std::pair<unsigned char, bool>(246,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("LSR", std::pair<unsigned char, bool>(247,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("ASR", std::pair<unsigned char, bool>(248,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("TST", std::pair<unsigned char, bool>(249,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("CLC", std::pair<unsigned char, bool>(250,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("SEC", std::pair<unsigned char, bool>(251,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("TCA", std::pair<unsigned char, bool>(252,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("TVA", std::pair<unsigned char, bool>(253,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("JAL", std::pair<unsigned char, bool>(254,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("NOP", std::pair<unsigned char, bool>(255,1)));
    op_dict.insert(std::pair<std::string, std::pair<unsigned char, bool> >("ORG", std::pair<unsigned char, bool>(255,0)));


    if (op_dict.find(opcode) == op_dict.end()) {
        int error_byte = 255 + get_error(5);
        return error_byte;
    }

    if (op_dict.find(opcode)->second.second != empty) {
        int error_byte = 255 + get_error(6);
        return error_byte;
    }

    if (!(opcode.compare("DAT")) || !(opcode.compare("ORG"))) {
        if ((arg < -128) || (arg > 255)) {
            int error_byte = 255 + get_error(6);
            return error_byte;
        }
        if (arg < 0)
            arg += 255;
        if (!(opcode.compare("ORG"))) {
            arg *= -1;
            arg -= 1;
            return arg;
        }
    }

    if (!(opcode.compare("EXT"))) {
        if (arg == 0) {
            int error_byte = 255 + get_error(5);
            return error_byte;
        }
    }

    if (opcode.compare("DAT") && (op_dict.find(opcode)->second.first < 240)) {
        if ((arg < -8) || (arg > 15)) {
            int error_byte = 255 + get_error(6);
            return error_byte;
        }
        if (arg < 0)
            arg += 16;
    }

    int byte = op_dict.find(opcode)->second.first + arg;

    return byte;

}
