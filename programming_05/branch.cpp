#include <iostream>


void STA(unsigned long int counts[3], unsigned long long int ba,
         unsigned long long int ta, bool T) {

    ((ta < ba) == T) ? counts[0]++ : counts[1]++;

}

void AH(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], unsigned long long int bdict[1024], unsigned long long int tdict[1024], char type) {

    unsigned int loc = (type == 'B') ? ba & 1023 : (type == 'T') ? ta & 1023 : ((ba & 31) << 5) + (ta & 31);
    if ((bdict[loc] != ba) || (tdict[loc] != ta)) { counts[2]++; }
    else { (hash[loc] == T) ? counts[0]++ : counts[1]++; }
    bdict[loc] = ba;
    tdict[loc] = ta;
    hash[loc] = T;

}

void COL(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], unsigned long long int bdict[1024], unsigned long long int tdict[1024]) {

    unsigned int loc = ba & 1023;
    if ((bdict[loc] != ba) || (tdict[loc] != ta)) { STA(counts,ba,ta,T); }
    else { (hash[loc] == T) ? counts[0]++ : counts[1]++; }
    bdict[loc] = ba;
    tdict[loc] = ta;
    hash[loc] = T;

}

void SAT(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], unsigned long long int bdict[1024], unsigned long long int tdict[1024]) {

    unsigned int loc = ba & 1023;
    if ((bdict[loc] != ba) || (tdict[loc] != ta)) { counts[2]++; }
    else { ((hash[loc] >= 2) == T) ? counts[0]++ : counts[1]++; }
    bdict[loc] = ba;
    tdict[loc] = ta;
    if (T) { hash[loc] += (hash[loc] == 3) ? 0 : 1; }
    else { hash[loc] -= (hash[loc] == 0) ? 0 : 1; }

}

void TWO(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], int pred[32],
         unsigned long long int bdict[1024], unsigned long long int tdict[1024]) {

    unsigned int loc = ba & 1023;
    if ((bdict[loc] != ba) || (tdict[loc] != ta)) { counts[2]++; }
    else { (pred[hash[loc]] == T) ? counts[0]++ : counts[1]++; }
    bdict[loc] = ba;
    tdict[loc] = ta;
    pred[hash[loc]] = T;
    hash[loc] = (hash[loc] << 1) & 31;
    if (T) { hash[loc]++; };
}


int main(int argc, char* argv[]) {

    if (argc > 1) { return 1; }
    unsigned long int counts[7][3] = {0};

    int bah_hash[1024] = {0};
    unsigned long long int bah_bdict[1024] = {0}, bah_tdict[1024] = {0};
    int tah_hash[1024] = {0};
    unsigned long long int tah_bdict[1024] = {0}, tah_tdict[1024] = {0};
    int bta_hash[1024] = {0};
    unsigned long long int bta_bdict[1024] = {0}, bta_tdict[1024] = {0};
    int col_hash[1024] = {0};
    unsigned long long int col_bdict[1024] = {0}, col_tdict[1024] = {0}; 
    int sat_hash[1024] = {0};
    unsigned long long int sat_bdict[1024] = {0}, sat_tdict[1024] = {0}; 
    int two_hash[1024] = {0};
    int two_pred[32] = {0};
    unsigned long long int two_bdict[1024] = {0}, two_tdict[1024] = {0};   

    unsigned long long int ba, ta;
    char flag;

    while (scanf("%llx %llx %c",&ba,&ta,&flag) == 3) {
        bool T = (flag == 84);

        STA(counts[0],ba,ta,T);
        AH(counts[1],ba,ta,T,bah_hash,bah_bdict,bah_tdict,'B');
        AH(counts[2],ba,ta,T,tah_hash,tah_bdict,tah_tdict,'T');
        AH(counts[3],ba,ta,T,bta_hash,bta_bdict,bta_tdict,'A');
        COL(counts[4],ba,ta,T,col_hash,col_bdict,col_tdict);
        SAT(counts[5],ba,ta,T,sat_hash,sat_bdict,sat_tdict);
        TWO(counts[6],ba,ta,T,two_hash,two_pred,two_bdict,two_tdict);
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
