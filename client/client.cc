/*
FILNAMN: 		smiley.cc
LABORATION:		
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
DATUM:			2013-11-14
BESKRIVNING:	
*/


#include "smiley.h"
#include "../server/message/message.h"
using namespace std;

int main()
{
    Smiley m;
    cout<<m.get("=(")<<"\n";
    cout<<m.find("=)")<<"\n";
    return 0;
}




