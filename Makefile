all: Q0466.c Q0467.c
	gcc Q0466.c -o 466.o
	gcc Q0467.c -o 467.o
	gcc Q0469.c -o 469.o
	gcc Q0470.c -o 470.o

%: %.c
	gcc $@.c -g -o test.o

test:
	./test.o

clean:
	rm *.o
