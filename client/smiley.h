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
#include <time.h>

class Smiley
{
public:
    Smiley(const referenceString, pictureDirectory;
    ~Smiley()=default;
    std::string getSmiley() const;
   
    void print() const;
    
private:
    std::string referenceString;
    std::string pictureDirectory;
    
    
};



#endif