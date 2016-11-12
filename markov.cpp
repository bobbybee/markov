#include <iostream>
#include <fstream>
#include <string.h>
#include <map>

typedef std::map<std::string, std::map<std::string, std::map<std::string, int>>> MarkovChain;

bool chain_initialized = false;
MarkovChain __chain;

extern "C" {
    void initialize_chain(char* p) {
        if(getenv("MARKOV_CHAIN")) p = getenv("MARKOV_CHAIN");

        std::string path(p);
        std::ifstream in(path);

        std::string a, b, c;
        int d;

        while (in >> a >> b >> c >> d) __chain[a][b][c] = d;

        chain_initialized = true;
    }

    ssize_t nextWord(char* out, size_t maximum, char* context, size_t len) {
        char* end = context + len - 1;

        int space = 1;

        while(*end && *end == ' ') {
            --end;
            space = 0;
        }

        std::string ult, pen;
        while (*end && *(end--) != ' ') ult = *(end+1) + ult;
        while (*end && *end == ' ') end--;
        while (*end && *(end--) != ' ') pen = *(end+1) + pen;

        std::map<std::string, int> kv = __chain[pen][ult];

        int sum = 0;
        for (auto it = kv.begin(); it != kv.end(); ++it) sum += it->second;

        if (sum == 0) return 0;

        int chosen = rand() % sum;

        for(auto it = kv.begin(); it < kv.end(); ++it) {
            chosen -= it->second;

            if(chosen <= 0) {
                if(it->first.length() + space >= maximum) return -1;
                
                if(trailingSpace) out[0] = ' ';
                strcpy(out + space, it->first.c_str());
                return it->first.length() + ex;
            }
        }

        return -1;
   }
}
