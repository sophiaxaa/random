CC = gcc
CFLAGS = -Wall -Wextra

prng: main.o lcg.o mersenne.o xorshift.o xorshiro.o
	$(CC) $(CFLAGS) -o prng main.o lcg.o mersenne.o xorshift.o xorshiro.o

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

lcg.o: lcg.c lcg.h 
	$(CC) $(CFLAGS) -c lcg.c

mersenne.o: mersenne.c mersenne.h 
	$(CC) $(CFLAGS) -c mersenne.c

xorshift.o: xorshift.c xorshift.h 
	$(CC) $(CFLAGS) -c xorshift.c

xorshiro.o: xorshiro.c xorshiro.h 
	$(CC) $(CFLAGS) -c xorshiro.c

clean: 
	rm -f *.o prng

run: prng
	./prng
