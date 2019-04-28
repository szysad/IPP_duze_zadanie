CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2

.PHONY: all clean

all: main.o mapNodeVector.o mapNode.o roadVector.o road.o city.o map_dev.o mapNodePriorityQueue.o vector.o mapNode_list.o
	$(CC) $(CFLAGS) main.o mapNodeVector.o mapNode.o roadVector.o road.o city.o map_dev.o mapNodePriorityQueue.o vector.o mapNode_list.o -o development

main.o: city.o road.o roadVector.o mapNode.o mapNodeVector.o map_dev.o mapNodePriorityQueue.o vector.o mapNode_list.o
	$(CC) $(CFLAGS) main.c -c -o main.o

map_dev.o: map_dev.c map_dev.h mapNodeVector.o mapNodePriorityQueue.o vector.o mapNode_list.o
	$(CC) $(CFLAGS) map_dev.c -c -o map_dev.o

mapNodeVector.o: mapNodeVector.c mapNodeVector.h mapNode.o
	$(CC) $(CFLAGS) mapNodeVector.c -c -o mapNodeVector.o

mapNodePriorityQueue.o: mapNodePriorityQueue.c mapNodePriorityQueue.h mapNode.o
	$(CC) $(CFLAGS) mapNodePriorityQueue.c -c -o mapNodePriorityQueue.o

mapNode_list.o: mapNode_list.c mapNode_list.h mapNode.o
	$(CC) $(CFLAGS) mapNode_list.c -c -o mapNode_list.o

mapNode.o: mapNode.c mapNode.h city.o roadVector.o
	$(CC) $(CFLAGS) mapNode.c -c -o mapNode.o

roadVector.o: roadVector.c roadVector.h road.o
	$(CC) $(CFLAGS) roadVector.c -c -o roadVector.o

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) vector.c -c -o vector.o

road.o: road.c road.h
	$(CC) $(CFLAGS) road.c -c -o road.o

city.o: city.c city.h
	$(CC) $(CFLAGS) city.c -c -o city.o

clean :
	rm -f *.o
	rm -f a.out
	rm -f development
	rm -f vgcore.*