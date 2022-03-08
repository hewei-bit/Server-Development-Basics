.PHONY: clean
CC = gcc
RM = rm
EXE = simple
OBJS = main.o foo.o

$(EXE): $(OBJS)
	@echo "exe into"
	$(CC) -o $@ $^
	@echo "exe leave"
%.o: %.c
	@echo "gcc -o -c"
	$(CC) -o $@ -c $^
clean:
	$(RM) $(EXE) $(OBJS)

