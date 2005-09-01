CC = gcc
CFLAGS = -Os -g -Wall -W -Wwrite-strings
LDFLAGS = 
O_TARGET = linklist
SRCS = main.c Linked.c
OBJS = main.o Linked.o

all:	$(OBJS)
	$(CC) $(LDFLAGS) -o $(O_TARGET) $(OBJS)

$(SRCS):
	$(CC) $(CFLAGS) -o $@ $*.c

clean:
	@rm *.o $(O_TARGET)
