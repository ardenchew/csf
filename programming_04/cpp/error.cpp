#include <iostream>

#include "error.h"

int get_error(int error) {
    switch (error) {
        case 1:
            std::cout << "Error: num args" << std::endl;
            return 1;
        case 2:
            std::cout << "Error: read file" << std::endl;
            return 2;
        case 3:
            std::cout << "Error: write file" << std::endl; 
            return 3;
        case 4:
            std::cout << "Error: program size" << std::endl; 
            return 4;
        case 5:
            std::cout << "Error: invalid opcode" << std::endl; 
            return 5;
        case 6:
            std::cout << "Error: invalid argument" << std::endl; 
            return 6;
        case 7:
            std::cout << "Error: invalid label" << std::endl;
            return 7;
        case 8:
            std::cout << "Error: unresolved reference" << std::endl;
            return 8;
        case 9:
            std::cout << "Error: memory allocation" << std::endl; 
            return 9;
        default:
            return -1;
    }
}

 
 

 
 

