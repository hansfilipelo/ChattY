#!/bin/bash

CLASS=$1
touch $CLASS.h
touch $CLASS.cc

cat << _EOF_ > ./$CLASS.h
/*
_EOF_

echo "FILNAMN: 		$CLASS.h" >> $CLASS.h

cat << _EOF_ >> ./$CLASS.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
_EOF_

echo "SKAPAD DATUM:	$(date '+%Y-%m-%d')" >> $CLASS.h

cat << _EOF_ >> ./$CLASS.h
BESKRIVNING:	
*/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>

_EOF_


cat << _EOF_ > ./$CLASS.cc
/*
_EOF_

echo "FILNAMN: 		$CLASS.cc" >> $CLASS.cc

cat << _EOF_ >> ./$CLASS.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
_EOF_

echo "SKAPAD DATUM:	$(date '+%Y-%m-%d')" >> $CLASS.cc

cat << _EOF_ >> ./$CLASS.cc
BESKRIVNING:	
*/

#include "$CLASS.h"

using namespace std;

_EOF_


echo "Skapat ny klass $CLASS"

