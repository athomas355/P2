CC = gcc
CFLAGS = -g
TARGET = frontEnd
OBJS = main.o parser.o scanner.o testTree.o

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


clean:
	/bin/rm -f *.o $(TARGET)