dijkstra.exe: dijkstra.o hash.o heap.o
	g++ -o dijkstra.exe hash.o heap.o dijkstra.o

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o dijkstraDebug.exe dijkstra.cpp heap.cpp hash.cpp

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
