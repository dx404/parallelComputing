CC=gcc

all: main

main: main.o nbody.o display.o
	$(CC) main.o nbody.o display.o -o main -lm
	
main.o: main.c
	$(CC) -c main.c

nbody.o: nbody.c
	$(CC) -c nbody.c

display.o: display.c
	$(CC) -c display.c

clean:
	rm -rf *.o
	rm main

run: 
	./main