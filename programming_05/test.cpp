#include <iostream>


void tester(int * a) {

    *a = 1;
}

int main() {


    int a = 0;

    tester(&a);

    std::cout << a << std::endl;
    
    return 0;

}
