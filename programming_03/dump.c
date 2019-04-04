#include <unistd.h>
#include "dump.h"

int dump(int encodings[], int byte_count, int dumpfile) {

    unsigned char c;
    for (int i = 0; i < byte_count; i++) {
        c = encodings[i];
        write(dumpfile,&c,1);
    }
    return 0;

}
