/*
 FILNAMN: 		message_test.cc
 LABORATION:
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 DATUM:			2013-11-14
 BESKRIVNING:
 */

#include "message.h"
using namespace std;

int main()
{
    Message m("hejsan, hur mår du?", "Tobias", "Niklas");
    m.print();
    return 0;
}
