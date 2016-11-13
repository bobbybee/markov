%.o: %.cpp
	g++ -c -fPIC -Wall -Wextra -Werror -pedantic $<

libmarkov.so: markov.o
	g++ -shared -fPIC -o $@ $<

.PHONY: install
install: /usr/local/lib/libmarkov.so /usr/local/include/markov.h

/usr/local/lib/libmarkov.so: libmarkov.so
	cp $< $@

/usr/local/include/markov.h: markov.h
	mkdir -p /usr/local/include
	cp $< $@
