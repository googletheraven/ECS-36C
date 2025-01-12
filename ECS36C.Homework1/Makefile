CC=g++
CFLAGS=-c -Wall -std=c++11

all: LinkedList

LinkedList: LinkedList.o LinkedListNode.o
	$(CC) $(CFLAGS) LinkedList.o LinkedListNode.o -o LinkedList

LinkedList.o: LinkedList.cpp LinkedList.hpp
	$(CC) $(CFLAGS) LinkedList.cpp

LinkedListNode.o: LinkedListNode.cpp LinkedListNode.hpp
	$(CC) $(CFLAGS) LinkedListNode.cpp

clean:
	rm -f *.o LinkedList