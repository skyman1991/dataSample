testmain.out: testmain.o test.o
	gcc -o ./out/testmain.out testmain.o test.o
testmain.o: testmain.c test.h
	gcc -c testmain.c
test.o: test.c test.h
	gcc -c test.c

.PHONY: clean
clean:
	rm testmain.o test.o
