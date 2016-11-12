#include <iostream>
#include <fstream>
#include <string.h>
#include <map>

typedef std::map<std::string, std::map<std::string, std::map<std::string, int>>> MarkovChain;

bool chain_initialized = false;
MarkovChain __chain;

extern "C" {

void initialize_chain(char* p) { 
    std::string path(p);
    std::ifstream in(path);

    std::string a, b, c;
    int d;

    while(in >> a >> b >> c >> d) {
        __chain[a][b][c] = d;
    }

    chain_initialized = true;
}

ssize_t nextWord(char* out, size_t maximum, char* context, size_t len) {
    if(!chain_initialized) initialize_chain("./chain.txt");

    char* end = context + len - 1;

    std::string ult, pen;
    while(*end && *(end--) != ' ') ult = *(end+1) + ult;
    while(*end && *(end--) != ' ') pen = *(end+1) + pen;

    std::map<std::string, int> kv;

    try {
        kv = __chain[pen][ult];
    } catch(const std::out_of_range& err) {
        out[0] = '\0';
        return 0;
    }

    int sum = 0;
    for(auto it = kv.begin(); it != kv.end(); ++it) sum += it->second;
    if(sum == 0) return -1;

    int chosen = rand() % sum;
    for(auto it = kv.begin(); it != kv.end(); ++it) {
        chosen -= it->second;

        if(chosen <= 0) {
            std::string str = it->first;

            if(str.length() < maximum) {
                strcpy(out, str.c_str());
                return str.length();
            } else {
                return -1;
            }
        }
    }

    return -1;
}

ssize_t advance_text(char* text, size_t length) {
    if(!chain_initialized) initialize_chain("./chain.txt");

    char next[64];
    ssize_t nextLen = nextWord(next, 64, text, strlen(text)) + 1;
    size_t l = strlen(text);

    if(nextLen == -1 || l + nextLen > length) return -1;

    text[l] = ' ';
    memcpy(text + l + 1, next, nextLen - 1);

    return nextLen;
}

}

/*int main() {
    initialize_chain("chain.txt");

    char* text = (char*) malloc(4096);
    memset(text, 0, 4095);
    strcpy(text, "this is");

    for(;;) {
        advance_text(text, 512);
        printf("%s\n", text);
    }
}*/
