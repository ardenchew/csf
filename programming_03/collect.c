#include <unistd.h>
#include "collect.h"

int collect(int *encodings, int readfile) {

    int byte_count = 0;
    unsigned char c[1]; 
    int n = read(readfile,c,1);
    int byte;

    while ((n != 0) && (byte_count < 256)) {
        byte = *c;
        encodings[byte_count] = byte;
        n = read(readfile,c,1);
        byte_count++;
    }

    return byte_count;

}
