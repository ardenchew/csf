#ifndef BRANCH_H
#define BRANCH_H

void STA(unsigned long int counts[3], unsigned long long int ba,
         unsigned long long int ta, bool T);

void AH(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], unsigned long long int bdict[1024], unsigned long long int tdict[1024], char type);

void COL(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], unsigned long long int bdict[1024], unsigned long long int tdict[1024]);

void SAT(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], unsigned long long int bdict[1024], unsigned long long int tdict[1024]);

void TWO(unsigned long int counts[3], unsigned long long int ba, unsigned long long int ta,
         bool T, int hash[1024], int pred[32],
         unsigned long long int bdict[1024], unsigned long long int tdict[1024]);

int main(int argc, char* argv[]);

#endif
