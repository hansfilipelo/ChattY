/*
FILNAMN: 		smiley.cc
LABORATION:		
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
DATUM:			2013-11-14
BESKRIVNING:	
*/


#include "smiley.h"
using namespace std;

Smiley::Smiley()
{
    const char* filename="smileys.txt";
    ifstream inputfile;
    inputfile.open(filename,ifstream::in);
    
    if (not(inputfile.good())) {
        cout<< "Error while opening file";
    }
    string key;
    string path;
    while (inputfile)
    {
        inputfile >> key;
        inputfile >> path;
        listOfSmileys.insert(pair<string,string>(key, path));
    }
}


string Smiley::get(string key) const
{
    return listOfSmileys.at(key);
}


bool Smiley::find(string key) const
{
    return listOfSmileys.count(key);
}