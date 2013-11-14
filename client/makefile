	CCC = g++
	CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra 

client: client.o smiley.o
	$(CCC) $(CCFLAGS) client.o smiley.o -o client

client.o: client.cc
	$(CCC) $(CCFLAGS) -c client.cc 

smiley.o: smiley.cc smiley.h
	$(CCC) $(CCFLAGS) -c smiley.cc

clean:
	@ \rm -f ./*.o
	@ \rm -f client
