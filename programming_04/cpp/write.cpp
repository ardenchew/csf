#include <stdio.h>
#include "error.h"

int write(unsigned char mem[], FILE * ofp) {

    int check;

    for (int i = 0; i < 256; i++) {
        check = fputc(mem[i], ofp);
        if (check == EOF)
            return get_error(3);
    }

    return 0;

}
