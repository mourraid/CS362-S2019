CFLAGS= -Wall -fpic -coverage -lm -std=c99

main:	testme.c
	gcc -o main testme.c $(CFLAGS)

clean:	
	rm -f main *.gcov *.gcda *.gcno
