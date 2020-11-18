CFLAGS+=  -pedantic -Wall -std=c99 -O3
HW=hw06

tar:
	tar -czvf ${HW}.tar.gz main.c

program: main.c
	${CC} ${CFLAGS} main.c -o main

clean:
	rm -f *.o
	rm -f main
	rm -f ${HW}.tar.gz

extar:
	tar -xzvf ${HW}.tar.gz main.c

.PHONY: clear tar