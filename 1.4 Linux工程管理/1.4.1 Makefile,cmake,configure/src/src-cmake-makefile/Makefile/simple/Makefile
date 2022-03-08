simple: main.o foo.o
	gcc -o simple main.o foo.o
main.o: main.c
	gcc -c main.c -o main.o
foo.o: foo.c
	gcc -c foo.c -o foo.o
clean:
	rm simple main.o foo.o


