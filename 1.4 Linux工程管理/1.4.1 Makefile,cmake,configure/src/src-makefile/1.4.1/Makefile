.PHONY: main clean
test: main foo.o
	gcc -o simple main.o foo.o
main: main.c
	gcc -o main.o -c main.c
foo.o: foo.c
	gcc -o foo.o -c foo.c
clean:
	rm simple main.o foo.o
