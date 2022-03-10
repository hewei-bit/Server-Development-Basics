.PHONY: all clean
MKDIR = mkdir
RM = rm
RMFLAGS = -fr
CC = gcc
EXE = complicated
DIRS = objs exes
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
all: $(DIRS) $(EXE)

$(DIRS):
	$(MKDIR) $@

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^
clean:
	$(RM) $(RMFLAGS) $(DIRS) $(EXE) $(OBJS)
