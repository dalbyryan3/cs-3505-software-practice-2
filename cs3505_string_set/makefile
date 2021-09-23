a.out: tester.o node.o string_set.o
	g++ -g tester.o node.o string_set.o

tester.o: node.h string_set.h tester.cpp
	g++ -g -c tester.cpp

node.o: node.cpp node.h
	g++ -g -c node.cpp

string_set.o: string_set.h node.h string_set.cpp
	g++ -g -c string_set.cpp

clean:
	rm -f tester.o node.o string_set.o a.out
