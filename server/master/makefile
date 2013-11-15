	CCC = g++
	CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra 
	OBJECTS = master_test.o message.o room.o User.o getTime.o

master_test: $(OBJECTS)
	$(CCC) $(CCFLAGS) master_test.o -o master_test

master_test.o: master_test.cc
	$(CCC) $(CCFLAGS) -c master_test.cc 

master.o: master.cc
	$(CCC) $(CCFLAGS) -c ../master/master.cc

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
	@ \rm -f master_test
