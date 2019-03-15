CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = dijkstra.o pqueue.o

test: dijkstra
	./dijkstra

debug: dijkstra
	gdb ./dijkstra

dijkstra : $(OFILES)
	$(LINK) -o dijkstra $(OFILES) 

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

dijkstra.o: dijkstra.cpp pqueue.h
	$(CC) $(CFLAGS) -c dijkstra.cpp

clean: 
	rm $(OFILES) dijkstra
