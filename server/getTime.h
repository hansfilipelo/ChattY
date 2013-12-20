/*
FILNAMN: 		getTime.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#ifndef getTime_H
#define getTime_H


#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

/*
 Gets current date and time. We now now that Qt has a built in class for doing exactly this but we built this using standard C++ libraries. 
 */

const std::string currentDateTime();

#endif