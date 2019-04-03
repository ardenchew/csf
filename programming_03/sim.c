#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "error.h"
#include "collect.h"
#include "process.h"

int main(int argc, const char* argv[]) {

    if ((argc > 3) || (argc == 2))
        return get_error(1,1);
    
    int readfile = (argc == 3) ? open(argv[1], O_RDONLY): 0;
    int writefile = (argc == 3) ? open(argv[2],O_WRONLY): 1;

    if (readfile < 0)
        return get_error(2,1);

    if (writefile < 0)
        return get_error(3,1);

    int encodings[256];
    int byte_count = collect(encodings, readfile);

    return process(encodings, byte_count, writefile);

}
