CC = gcc
CFLAGS = -g
TARGET = statSem
OBJS = main.o parser.o scanner.o testTree.o stack.o

#%.o: %.c
	#$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: 
	$(CC) $(CFLAGS) -c main.c

parser.o: 
	$(CC) $(CFLAGS) -c parser.c

scanner.o: 
	$(CC) $(CFLAGS) -c scanner.c

testTree.o: 
	$(CC) $(CFLAGS) -c testTree.c

stack.o:
	$(CC) $(CFLAGS) -c stack.c

:
clean:
	/bin/rm -f *.o $(TARGET)
