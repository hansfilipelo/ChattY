	CCC = g++
	CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra 
	OBJECTS = room_test.o message.o room.o User.o getTime.o

room_test: $(OBJECTS)
	$(CCC) $(CCFLAGS) room_test.o -o room_test

room_test.o: room_test.cc
	$(CCC) $(CCFLAGS) -c room_test.cc 

message.o: ../message/message.cc 
	$(CCC) $(CCFLAGS) -c ../message/message.cc

room.o: ../room/room.cc
	$(CCC) $(CCFLAGS) -c ../room/room.cc

User.o: ../user/User.cc
	$(CCC) $(CCFLAGS) -c ../user/User.cc

getTime.o: ../getTime.cc
	$(CCC) $(CCFLAGS) -c ../getTime.cc

clean:
	@ \rm -f ./*.o
	@ \rm -f room_test
