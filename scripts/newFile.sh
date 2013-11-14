#!/bin/bash

FILE=$1
touch $FILE

cat << _EOF_ > ./$FILE
/*
_EOF_

echo "FILNAMN: 		$FILE" >> $FILE

cat << _EOF_ >> ./$FILE
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
_EOF_

echo "SKAPAD DATUM:	$(date '+%Y-%m-%d')" >> $FILE

cat << _EOF_ >> ./$FILE
BESKRIVNING:	
*/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
	
	return 0;
}
_EOF_

echo "Skapat ny $FILE"
