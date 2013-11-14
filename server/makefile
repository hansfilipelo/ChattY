	CCC = g++
	CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra 
	OBJECTS = room_test.o message.o room.o User.o getTime.o

room_test: $(OBJECTS)
	$(CCC) $(CCFLAGS) room_test.o -o room_test

room_test.o: room_test.cc
	$(CCC) $(CCFLAGS) -c room_test.cc 

message.o: message.cc 
	$(CCC) $(CCFLAGS) -c message.cc

room.o: room.cc
	$(CCC) $(CCFLAGS) -c room.cc

User.o: User.cc
	$(CCC) $(CCFLAGS) -c User.cc

getTime.o: getTime.cc
	$(CCC) $(CCFLAGS) -c getTime.cc

clean:
	@ \rm -f ./*.o
