all: control write

control: control.o
	gcc -o control control.o

control.o: control.c game.h
	gcc -c control.c

write: write.o
	gcc -o write write.o

write.o: write.c game.h
	gcc -c write.c
