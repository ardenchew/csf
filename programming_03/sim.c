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

int main(int argc, const char* argv[]) {

    if ((argc > 3) or (argc == 2)) {
        write(1, "Error: num args\n", 16);
        return 1;
    }
    
    int readfile = (argc == 3) ? open(argv[1], O_RDONLY): 0;
    int writefile = (argc == 3) ? open(argv[1],O_WRONLY): 1;

    if (readfile < 0) {
        write(1, "Error: file reading\n", 20);
        return 2;
    }

    if (writefile < 0) {
        write(1, "Error: file writing\n", 20);
        return 3;
    }


    

}
