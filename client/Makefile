obj = main.o ad7606.o data.o sock.o
objects = obj/main.o obj/ad7606.o obj/data.o obj/sock.o
header = ./include/ad7606.h ./include/data.h ./include/sock.h
CFLAGS = -g -I ./include

vpath %.c ./src
vpath %.h ./include
vpath %.o ./obj

main: $(obj)
	gcc $(objects) -o ./bin/main -lwiringPi -lapue
main.o: $(header)
	gcc -c $(CFLAGS) ./src/main.c -o obj/main.o
ad7606.o: $(header)
	gcc -c $(CFLAGS) ./src/ad7606.c -o obj/ad7606.o
data.o: data.h
	gcc -c $(CFLAGS) ./src/data.c -o obj/data.o
sock.o: sock.h
	gcc -c $(CFLAGS) ./src/sock.c -o obj/sock.o

.PHONY: clean
clean:
	rm ./obj/*.o
