CXX=gcc-12
all: Q0466.c Q0467.c Q0469.c Q0470.c Q04701.c
	gcc Q0466.c -o 466.o
	gcc Q0467.c -o 467.o
	gcc Q0469.c -o 469.o
	gcc Q0470.c -o 470.o
	gcc Q04701.c -o 4701.o

%: %.c
	$(CXX) $@.c -g -o test.o -Wall

test:
	./test.o

clean:
	Q0469
	Q0470
	code
	test.o
