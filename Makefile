%.o: %.cpp
	g++ -c -fPIC -Wall -Wextra -Werror -pedantic $<

libmarkov.so: markov.o
	g++ -shared -fPIC -o $@ $<

.PHONY: install
install: libmarkov.so markov.h
	cp libmarkov.so /usr/local/lib/
	cp markov.h /usr/local/include/
