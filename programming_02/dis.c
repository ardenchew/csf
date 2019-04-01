#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

const char hex2asc[17] = "0123456789ABCDEF";
const char *mnemonics[32] = {"EXT", "LDA", "LDI", "STA",
                             "STI", "ADD", "SUB", "JMP", "JMZ",
                             "AND", "IOR", "XOR", "ADL", "ADC",
                             "SBB", "NEG", "COM", "CLR", "SET",
                             "RTL", "RTR", "LSL", "LSR", "ASR",
                             "TST", "CLC", "SEC", "TCA", "TVA",
                             "JAL", "NOP", "HLT"};


int main(int argc, const char* argv[]) {

    // check number of arguments
    if (argc > 2) {
        write(1, "Error: num args\n", 16);
        return 1;
    }
    
    //where to read from
    int filedesc = (argc == 2) ? open(argv[1], O_RDONLY): 0;
    if (filedesc < 0) {
        write(1, "Error: file reading\n",20);   
        return 2;
    }

    unsigned char *c;
    int n = read(filedesc,c,1);

    while (n != 0) {
        int encoding = *c;
        int opcode = encoding >> 4;
        int operand = encoding & 15;

        write(1,"0x",2);
        write(1,&hex2asc[opcode],1);
        write(1,&hex2asc[operand],1);
        write(1,"  ",2);

        if ((opcode == 0) && (operand == 0)){
            write(1, mnemonics[31], 3);
        } else if (opcode < 15) {
            write(1, mnemonics[opcode], 3);
            write(1, " 0x", 3);
            write(1, &hex2asc[operand], 1);
        } else {
            write(1, mnemonics[opcode + operand], 3);
        }
        
        write(1, "\n", 1);
        n = read(filedesc,c,1);
    }

    return 0;
}
