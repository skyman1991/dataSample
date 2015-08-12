obj = main.o ad7606.o data.o
objects = obj/main.o obj/ad7606.o obj/data.o
header = ad7606.h data.h
CFLAGS = -g -I ./include

vpath %.c ./src
vpath %.h ./include
vpath %.o ./obj

main: $(obj)
	gcc $(objects) -o bin/main -lwiringPi -lapue
main.o: $(header)
	gcc -c $(CFLAGS) ./src/main.c -o obj/main.o
ad7606.o: $(header)
	gcc -c $(CFLAGS) ./src/ad7606.c -o obj/ad7606.o
data.o: data.h
	gcc -c $(CFLAGS) ./src/data.c -o obj/data.o

.PHONY: clean
clean:
	rm ./obj/*.o
