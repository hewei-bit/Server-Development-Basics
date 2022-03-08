.PHONY: clean
CC = gcc
RM = rm
EXE = simple
#SRCS = main.c foo.c
SRCS = $(wildcard *.c)
# 把.c换成对应的.o
#OBJS = foo.o foo2.o main.o
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(EXE): $(OBJS)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) -o $@ -c $^
clean:
	$(RM) $(EXE) $(OBJS)
src: # 测试make src显示相应的xx.c
	@echo $(SRCS)
objs:# 测试make objs显示相应的xx.o
	@echo $(OBJS)