#include <iostream>


void STA(unsigned long int counts[3], unsigned long long int ba,
         unsigned long long int ta, bool T) {

    if (ta < ba) {
        if (T) 
            counts[0]++;
        else
            counts[1]++;
    } else {
        if (T)
            counts[1]++;
        else
            counts[0]++;
    }
}

void BAH(unsigned long int counts[3], unsigned long long int ba,
         bool T, int hash[1024]) {

    if (hash[ba & 1023]) {
        if (T) {
            counts[0]++;
        } else {
            counts[1]++;
            hash[ba & 1023] = 0;
        }
    } else {
        if (T) {
            counts[1]++;
            hash[ba & 1023] = 1;
        } else {
            counts[0]++;
        }
    }


}

int main(int argc, char* argv[]) {

    if (argc > 1)
         return 1;

    //initialize counts
    unsigned long int counts[7][3];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            counts[i][j] = 0;
        }
    }

    int bah_hash[1024];
    for (int i = 0; i < 1024; i++) {
        bah_hash[i] = 0;
    }

    unsigned long long int ba;
    unsigned long long int ta;
    char flag;

    while (scanf("%llx %llx %c",&ba,&ta,&flag) == 3) {
        bool T = (flag == 84);

        STA(counts[0],ba,ta,T);
        BAH(counts[1],ba,T,bah_hash);

    }


    printf("STA: %20llu %20llu %20llu\n",counts[0][0],counts[0][1],counts[0][2]);
    printf("BAH: %20llu %20llu %20llu\n",counts[1][0],counts[1][1],counts[1][2]);
    printf("TAH: %20llu %20llu %20llu\n",counts[2][0],counts[2][1],counts[2][2]);
    printf("BTA: %20llu %20llu %20llu\n",counts[3][0],counts[3][1],counts[3][2]);
    printf("COL: %20llu %20llu %20llu\n",counts[4][0],counts[4][1],counts[4][2]);
    printf("SAT: %20llu %20llu %20llu\n",counts[5][0],counts[5][1],counts[5][2]);
    printf("TWO: %20llu %20llu %20llu\n",counts[6][0],counts[6][1],counts[6][2]);


    return 0;

}
