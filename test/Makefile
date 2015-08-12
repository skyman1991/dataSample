vpath %.c ./src
vpath %.o ./obj
vpath %.h ./include 
main: test.o
	gcc -o ./bin/main obj/test.o
test.o: test.c test.h
	gcc -c ./src/test.c -o obj/test.o

.PHONY: clean
clean:
	rm testmain.o test.o
