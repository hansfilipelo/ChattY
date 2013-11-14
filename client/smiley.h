/*
 FILNAMN: 		smiley.h
 LABORATION:
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 DATUM:			2013-11-14
 BESKRIVNING:
 */

#ifndef SMILEY
#define SMILEY
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>


class Smiley
{
public:
    Smiley();
    std::string get(std::string) const;
    bool find(std::string) const;
private:
    std::map<std::string,std::string> listOfSmileys;
};


#endif