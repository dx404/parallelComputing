CC=gcc -O3

all: main.out

main.out: main.o nbody.o display.o
	$(CC) main.o nbody.o display.o -o main.out -lm

main.o: main.c
	$(CC) -c main.c

nbody.o: nbody.c
	$(CC) -c nbody.c

display.o: display.c
	$(CC) -c display.c

clean:
	rm -rf *.o
	rm main.out

run: 
	./main.out

