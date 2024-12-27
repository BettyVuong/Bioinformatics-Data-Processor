vuongBettyA1: vuongBettyA1.o vuongBettyA1Main.o
	gcc vuongBettyA1.o vuongBettyA1Main.c -o vuongBettyA1 -lm
vuongBettyA1.o: vuongBettyA1.c givenA1.h
	gcc -Wall -std=c99 -c vuongBettyA1.c -lm
vuongBettyA1Main.o: vuongBettyA1Main.c givenA1.h
	gcc -Wall -std=c99 -c vuongBettyA1Main.c -lm
clean:
	rm*.o vuongBettyA1
