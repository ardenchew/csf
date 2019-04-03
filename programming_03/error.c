#include <unistd.h>
#include "error.h"

int get_error(int error, int writefile) {
    switch (error) {
        case 1:
            write(writefile,"Error: num args\n",16);
            return 1;
        case 2:
            write(writefile,"Error: file reading\n",20);
            return 2;
        case 3:
            write(writefile,"Error: file writing\n",20);
            return 3;
        case 4:
            write(writefile,"Error: execute unavailable data\n",32);
            return 4;
        case 5:
            write(writefile,"Error: read unavailable data\n",29);
            return 5;
        case 6:
            write(writefile,"Error: write unavailable data\n",30);
            return 6;
        default:
            return -1;
    }
}

 
 

 
 

