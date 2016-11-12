#ifndef __MARKOV
#define __MARKOV

void initialize_chain(char* path);
ssize_t advance_text(char* text, size_t length);
ssize_t nextWord(char* out, size_t maximum, char* context, size_t len);

#endif
