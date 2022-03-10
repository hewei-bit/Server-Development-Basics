.PHONY: clean
CC = gcc
RM = rm
EXE = simple
OBJS = main.o foo.o

$(EXE): $(OBJS)
	@echo "EXE:OBJS -> \$$@ = $@, $$^ = $^"
	$(CC) -o $@ $^
main.o: main.c
	@echo "main.o:main.c -> \$$@ = $@, $$^ = $^"
	$(CC) -o $@ -c $^
foo.o: foo.c
	@echo "foo.o:foo.c -> \$$@ = $@, $$^ = $^"
	$(CC) -o $@ -c $^
clean:
	$(RM) $(EXE) $(OBJS)

