	CCC = g++
	CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra 

message_test: message_test.o message.o
	$(CCC) $(CCFLAGS) message_test.o message.o -o message_test

message_test.o: message_test.cc
	$(CCC) $(CCFLAGS) -c message_test.cc 

message.o: message.cc message.h
	$(CCC) $(CCFLAGS) -c message.cc

clean:
	@ \rm -f ./*.o

