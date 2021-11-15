OBJ = heap.o  mvm.o dijkstra.o graph.o
COMP = gcc -fPIC -g -c -Wall

mvm.so: $(OBJ)
	gcc -shared -Wl,-soname,libmvm.so.1.0 -o libmvm.so $(OBJ) -lm

mvm: $(OBJ)
	gcc -g -o mvm $(OBJ) -lm

mvm.o: mvm.c heap.h mvm.h
	$(COMP) mvm.c
heap.o:  heap.c heap.h mvm.h
	$(COMP) heap.c
dijkstra.o:  dijkstra.c mvm.h dijkstra.h
	$(COMP) dijkstra.c

graph.o:  graph.c graph.h
	$(COMP) graph.c
.PHONY: clean
clean:
	rm *.o
