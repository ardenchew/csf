#include <unistd.h>
#include "error.h"
#include "process.h"

const char hex2asc[17] = "0123456789ABCDEF";
const char *mnemonics[] = {"EXT", "LDA", "LDI", "STA", "STI",
                             "ADD", "SUB", "JMP", "JMZ", "AND",
                             "IOR", "XOR", "ADL", "ADC", "SBB",
                             "NEG", "COM", "CLR", "SET", "RTL",
                             "RTR", "LSL", "LSR", "ASR", "TST",
                             "CLC", "SEC", "TCA", "TVA", "JAL",
                             "NOP", "HLT"};

int process(int *encodings, int byte_count) {

    int writefile = 1;

    int acc, opcode, operand;
    int pc = 0, halt = 0, set_carry = 0;
    int ext = 0, zero_flag = 0, carry = 0;

    while ((!halt) && (pc < byte_count)) {

        opcode = encodings[pc] >> 4;
        operand = encodings[pc] & 15;

        if (ext) {
            operand += (ext << 4);
            ext = 0;
        }

        write(writefile,"0x",2);
        write(writefile,&hex2asc[pc >> 4],1);
        write(writefile,&hex2asc[pc & 15],1);
        write(writefile,"  ",2);
        if ((opcode == 0) && (operand == 0)) {
            write(writefile,"HLT     ",8);
        } else if (opcode == 15) {
            write(writefile, mnemonics[opcode + (operand & 15)], 3);
            write(writefile,"     ",5);
        } else {
            write(writefile, mnemonics[opcode], 3);
            write(writefile," 0x",3);
            write(writefile,&hex2asc[operand >> 4],1);
            write(writefile,&hex2asc[operand & 15],1);
        } 

        switch (opcode) {
            case 0: //HLT or EXT
                if (operand == 0) {
                    halt++;
                    break;
                }
                ext = operand;
                break;
            case 1: //LDA
                if (operand >= byte_count) 
                    return get_error(5,1);
                acc = encodings[operand];
                break;
            case 2: //LDI
                if (operand >= byte_count)
                    return get_error(5,1);
                else if (encodings[operand] >= byte_count)
                    return get_error(5,1);
                acc = encodings[encodings[operand]];
                break;
            case 3: //STA
                if (operand >= byte_count)
                    return get_error(6,1);
                encodings[operand] = acc;
                break;
            case 4: //STI
                if (operand >= byte_count)
                    return get_error(6,1);
                else if (encodings[operand] >= byte_count)
                    return get_error(6,1);
                encodings[encodings[operand]] = acc;
                break;
            case 5: //ADD
                if (operand >= byte_count)
                    return get_error(5,1);
                acc += encodings[operand];
                set_carry = 1;
                break;
            case 6: //SUB
                if (operand >= byte_count)
                    return get_error(5,1);
                acc += (encodings[operand] ^ 255) + 1;
                set_carry = 1;
                break;
            case 7: //JMP
                if (operand >= byte_count) 
                    return get_error(4,1);
                pc = operand - 1;
                break;
            case 8: //JMZ
                if (zero_flag) {
                    if (operand >= byte_count)
                        return get_error(4,1);
                    pc = operand - 1;
                }
                break;
            case 9: //AND
                if (operand >= byte_count)
                    return get_error(5,1);
                acc &= encodings[operand];
                break;
            case 10: //IOR
                if (operand >= byte_count)
                    return get_error(5,1);
                acc |= encodings[operand];
                break;
            case 11: //XOR
                if (operand >= byte_count)
                    return get_error(5,1);
                acc ^= encodings[operand];
                break;
            case 12: //ADL
                operand = (operand >> 3) ? operand + 240: operand;
                acc += operand;
                set_carry = 1;
                break;
            case 13: //ADC
                if (operand >= byte_count)
                    return get_error(5,1);
                acc += encodings[operand] + carry;
                set_carry = 1;
                break;
            case 14: //SBB
                if (operand >= byte_count)
                    return get_error(5,1);
                acc += (encodings[operand] ^ 255) + carry;
                set_carry = 1;
                break;
            case 15:
                switch (operand) {
                    case 0: //NEG
                        acc = ((acc ^ 255) + 1) & 255;
                        break;
                    case 1: //COM
                        acc = (acc ^ 255);
                        break;
                    case 2: //CLR
                        acc = 0;
                        break;
                    case 3: //SET
                        acc = 255;
                        break;
                    case 4: //RTL
                        acc = ((acc << 1) | (acc >> 7)) & 255;
                        break;
                    case 5: //RTR
                        acc = ((acc << 7) | (acc >> 1)) & 255;
                        break;
                    case 6: //LSL
                        acc = (acc << 1) & 254;
                        break;
                    case 7: //LSR
                        acc = (acc >> 1) & 127;
                        break;
                    case 8: //ASR
                        acc = ((acc >> 1) & 127) | (acc & 128);
                        break;
                    case 9: //TST
                        acc = (zero_flag) ? acc: 1;
                        break;
                    case 10: //CLC
                        carry = 0;
                        break;
                    case 11: //SEC
                        carry = 1;
                        break;
                    case 12: //TCA
                        acc = carry;
                        break;
                    case 13: //TVA
                        acc = carry ^ (acc >> 7);
                        break;
                    case 14: //JAL
                        if (acc > byte_count)
                            return get_error(4,1);
                        acc ^= pc;
                        pc ^= acc;
                        acc ^= pc;
                        acc += 1;
                        pc -= 1;
                        break;
                    case 15: //NOP
                        break;
                }
                break;
            default:
                write(1,"Fuck\n",5);
                return 42;

        }

        if (set_carry) {
            carry = ((acc > 255) || (acc < 0)) ? 1: 0;
            set_carry = 0;
        }

        if (acc > 255) 
            acc = acc & 255;
        else if (acc < 0)
            acc = 0;

        write(writefile,"    ACC=0x",10);
        write(writefile,&hex2asc[(acc >> 4) & 15],1);
        write(writefile,&hex2asc[acc & 15],1);
        write(writefile,"\n",1);

        zero_flag = (acc == 0) ? 1: 0;
        pc++;
    }

    return 0;
}
