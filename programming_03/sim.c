#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "error.h"
#include "collect.h"
#include "process.h"
#include "dump.h"

int main(int argc, const char* argv[]) {

    if (argc > 3) 
        return get_error(1,1);

    int readfile = (argc == 1) ? 0: open(argv[1], O_RDONLY);
    int dumpfile = (argc == 3) ? open(argv[2],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR): 1;

    if (readfile < 0)
        return get_error(2,1);

    if (dumpfile < 0)
        return get_error(3,1);

    int encodings[256];
    int byte_count = collect(encodings, readfile);

    int ret = process(encodings, byte_count);
    if (ret)
        return ret;

    return dump(encodings, byte_count, dumpfile);

}
