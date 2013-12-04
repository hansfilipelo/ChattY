/*
FILNAMN: 		message.cc
LABORATION:		
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
DATUM:			2013-11-14
BESKRIVNING:	
*/


#include "message.h"
using namespace std;

Message::Message(const std::string message_, const std::string from_,const std::string to_,)
{
    message = message_;
    from = from_;
    to = to_;
    localTime = currentDateTime();
}

string Message::getMessage() const
{
    return message;
}

string Message::getFrom() const
{
    return from;
}

string Message::getTo()const
{
    return to;
}

string Message::getLocalTime() const
{
    return localTime;
}

void Message::setServerTime(const string serverTime_)
{
    serverTime = serverTime_;
}

string Message::getServerTime() const
{
    return serverTime;
}

void Message::print() const
{
    cout<<to<<" "<<localTime<< "\n"<<from<< " says: "<<message<<"\n";
}



