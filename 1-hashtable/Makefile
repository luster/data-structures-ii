spell.exe: spellcheck.o hash.o
	g++ -o spell.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	g++ -c spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o spellDebug.exe spellcheck.cpp hash.cpp

clean:
	rm -rf *.exe *.o *.stackdump *~ .*.swp .*.*.swp *.*.dSYM

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
