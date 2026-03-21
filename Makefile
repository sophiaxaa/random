CC = gcc
CFLAGS = -Wall -Wextra

prng: main.o lcg.o 
	$(CC) $(CFLAGS) -o prng main.o lcg.o 

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

lcg.o: lcg.c lcg.h 
	$(CC) $(CFLAGS) -c lcg.c

clean: 
	rm -f *.o prng

run: prng
	./prng
