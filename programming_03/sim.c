#include <unistd.h>
#include <fcntl.h>

const char hex2asc[17] = "0123456789ABCDEF";
const char *mnemonics[32] = {"EXT", "LDA", "LDI", "STA", "STI",
                             "ADD", "SUB", "JMP", "JMZ", "AND",
                             "IOR", "XOR", "ADL", "ADC", "SBB",
                             "NEG", "COM", "CLR", "SET", "RTL",
                             "RTR", "LSL", "LSR", "ASR", "TST",
                             "CLC", "SEC", "TCA", "TVA", "JAL",
                             "NOP", "HLT"};
int encodings[256];

const char error1[16] = "Error: num args\n";
const char error2[20] = "Error: file reading\n";
const char error3[20] = "Error: file writing\n";
const char error4[32] = "Error: execute unavailable data\n";
const char error5[29] = "Error: read unavailable data\n";
const char error6[30] = "Error: write unavailable data\n";
const int error_size[7] = {0,16,20,20,32,29,30};

int main(int argc, const char* argv[]) {

    if ((argc > 3) || (argc == 2)) {
        write(1, error1, error_size[1]);
        return 1;
    }
    
    int readfile = (argc == 3) ? open(argv[1], O_RDONLY): 0;
    int writefile = (argc == 3) ? open(argv[2],O_WRONLY): 1;

    if (readfile < 0) {
        write(1, error2, error_size[2]);
        return 2;
    }

    if (writefile < 0) {
        write(1, error3, error_size[3]);
        return 3;
    }

    int byte_count = 0;
    unsigned char c[1];
    int n = read(readfile,c,1);

    while ((n != 0) && (byte_count < 256)) {
        byte_count++;
        int encoding = *c;
        encodings[byte_count] = encoding;
        n = read(readfile,c,1);
    }

    int num_bytes = byte_count;
    int acc, opcode, operand;
    int pc = 0, halt = 0;
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
                if (operand >= byte_count) {
                    write(1,error5,error_size[5]);
                    return 5;
                }
                acc = encodings[operand];
                break;
            case 2: //LDI
                if (operand >= byte_count) { 
                    write(1,error5,error_size[5]);
                    return 5;
                } else if (encodings[operand] >= byte_count) {
                    write(1,error5,error_size[5]);
                    return 5;
                }
                acc = encodings[encodings[operand]];
                break;
            case 3: //STA
                if (operand >= byte_count) {
                    write(1,error6,error_size[6]);
                    return 6;
                }
                encodings[operand] = acc;
                break;
            case 4: //STI
                if (operand >= byte_count) {
                    write(1,error6,error_size[6]);
                    return 6;
                } else if (encodings[operand] >= byte_count) {
                    write(1,error6,error_size[6]);
                    return 6;
                }
                encodings[encodings[operand]] = acc;
                break;
            case 5: //ADD
                if (operand >= byte_count) {
                    write(1,error5,error_size[5]);
                    return 5;
                }
                acc += encodings[operand];
                break;
            case 6: //SUB
                if (operand >= byte_count) {
                    write(1,error5,error_size[5]);
                    return 5; 
                }
                acc -= encodings[operand];
                break;
            case 7: //JMP
                if (operand >= byte_count) {
                    write(1,error4,error_size[4]);
                    return 4;
                }
                pc = operand - 1;
                break;
            case 8: //JMZ
                if (zero_flag) {
                    if (operand >= byte_count) {
                        write(1,error4,error_size[4]);
                        return 4;
                    }
                    pc = operand - 1;
                }
                break;
            default:
                write(1,"Fuck\n",5);
                return 42;

        }

        write(writefile,"    ACC=0x",10);
        write(writefile,&hex2asc[acc >> 4],1);
        write(writefile,&hex2asc[acc & 15],1);
        write(writefile,"\n",1);
        zero_flag = (acc == 0) ? 1: 0;
        pc++;
    }
    

}
