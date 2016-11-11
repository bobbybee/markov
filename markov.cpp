#include <iostream>
#include <string.h>
#include "chain.h"

ssize_t nextWord(char* out, size_t maximum, char* context) {
    char* end = context + strlen(context) - 1;

    std::string ult, pen;
    while( *(end--) != ' ' && *(end + 1)) ult = *(end+1) + ult;
    while( *(end--) != ' ' && *(end + 1)) pen = *(end+1) + pen;

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

void advance_text(char* text, size_t length) {
    char next[64];
    ssize_t nextLen = nextWord(next, 64, text);

    if(nextLen == -1) {
        /* error condition */
        exit(1);
    }

    size_t l = strlen(text);

    if(l + nextLen + 1 > length) {
        exit(1);
    }

    text[l] = ' ';
    memcpy(text + l + 1, next, nextLen);
}

int main() {
    printf("Hello World!\n");
    printf("%d\n", __chain["very"]["small"]["markov "]);
    
    char* text = (char*) malloc(4096);
    memset(text, 0, 4095);
    strcpy(text, "this is some very small");

    for(;;) {
        advance_text(text, 4096);
        printf("%s\n", text);
    }
}
