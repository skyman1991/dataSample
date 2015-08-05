main.out:main.o ad7606.o data.o
	gcc -g -o run main.o ad7606.o data.o -lwiringPi -lapue
main.o:ad7606.h data.h
	gcc -g -c main.c
ad7606.o: ad7606.h data.h
	gcc -g -c ad7606.c
data.o:data.h
	gcc -g -c data.c

.PHONY: clean
clean:
	rm *.o
