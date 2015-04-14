aetg: main.o hashtable.o pair.o
	g++ -o aetg main.o hashtable.o pair.o
main.o: main.cpp hashtable.h pair.h
	g++ -c main.cpp
hashtable.o: hashtable.cpp hashtable.h pair.h
	g++ -c hashtable.cpp
pair.o: pair.cpp pair.h
	g++ -c pair.cpp
clean:
	rm *.o
	rm aetg
run:
	./aetg