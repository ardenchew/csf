#include <stdio.h>
#include <vector>

void DIR(unsigned long long int counts[2],
         unsigned long long int cache[8192],
         unsigned long long int address) {
   (cache[address & 8191] == address) ? counts[0]++ : counts[1]++;
   cache[address & 8191] = address;
}

int ASS(unsigned long long int counts[2],
         std::vector<unsigned long long int> *cache,
         unsigned long long int address, int size, bool S, bool P) {
   
    int idx = 0;
    for (std::vector<unsigned long long int>::iterator it = cache->begin(); it != cache->end(); ++it,idx++) {
        if (*it == address) {
            counts[0]++;
            cache->erase(cache->begin()+idx);
            cache->push_back(address);
            return 0;
        }
    }
    
    counts[1]++;
    if (!S) {
        if (cache->size() == size) { cache->erase(cache->begin()); } 
        cache->push_back(address);
    }
    return 1;
}

int main(int argc, char* argv[]) {

    if (argc > 1) { return 1; }
    unsigned long long int counts[7][2] = {0};

    unsigned long long int dir_cache[8192] = {0};
    std::vector<unsigned long long int> ass_cache;
    
    std::vector<unsigned long long int> set_cache[2048];
    std::vector<unsigned long long int> blk_cache[256];
    std::vector<unsigned long long int> nwa_cache[256];
    std::vector<unsigned long long int> prf_cache[256];


    unsigned long long int address;
    char flag;

    while (scanf("%llx %c",&address,&flag) == 2) {
        bool S = (flag == 83);
        
        DIR(counts[0],dir_cache,address);
        ASS(counts[1],&ass_cache,address,8192,0,0);
        ASS(counts[2],&set_cache[address & 2047],address,4,0,0);
        ASS(counts[3],&blk_cache[(address & 2047) >> 3],(address - (address & 7)),4,0,0);
        ASS(counts[4],&nwa_cache[(address & 2047) >> 3],(address - (address & 7)),4,S,0);
        int p = ASS(counts[5],&prf_cache[(address & 2047) >> 3],(address - (address & 7)),4,S,1);
        if (p && !S) {
            address += 8;
            ASS(counts[6],&prf_cache[(address & 2047) >> 3],(address - (address & 7)),4,S,1); 
        }
    }

    printf("DIR: %20llu %20llu\n",counts[0][0],counts[0][1]);
    printf("ASS: %20llu %20llu\n",counts[1][0],counts[1][1]);
    printf("SET: %20llu %20llu\n",counts[2][0],counts[2][1]);
    printf("BLK: %20llu %20llu\n",counts[3][0],counts[3][1]);
    printf("NWA: %20llu %20llu\n",counts[4][0],counts[4][1]);
    printf("PRF: %20llu %20llu\n",counts[5][0],counts[5][1]);

}
