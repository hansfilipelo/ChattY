/*
FILNAMN: 		smiley.cc
LABORATION:		
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
DATUM:			2013-11-14
BESKRIVNING:	
*/


#include "smiley.h"
using namespace std;

Smiley::Smiley(const string referenceString_, const string pictureDirectory_)
{
    referenceString = referenceString_;
    pictureDirectory = pictureDirectory_;
}

string Message::getSmiley() const
{
    return pictureDirectory;
}




