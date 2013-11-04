/*
FILNAMN: 		Lab1-4.CC
LABORATION:		1	
PROGRAMMERARE:	niker917, davha227
DATUM:			2013-09-18
BESKRIVNING:	Laboration 1-4, läser in ord som matas in, orden transformerar orden till små bokstäver, 
				sorterar orden och räknar hur många av samma ord som förekommit men hjälp av objekt i en vektor.
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <math.h>
using namespace std;

//skapar klassen word_entry
struct	word_entry
{
	string word;
	unsigned int count;	
};

//Skapar objekt från input och lägger till ordet på rätt plats i wordlist
static void insert(vector<word_entry>& wordlist, const string& input)
{
	word_entry temp;
	temp.count=1;
	temp.word=input;
	unsigned long vector_size=wordlist.size(); 

	for(unsigned int element=0;element<vector_size;element++)
	{	
		if(input==wordlist.at(element).word)
		{
			wordlist.at(element).count++;
			return;
		}
		else if(wordlist.at(element).word>input)
		{
			wordlist.insert(element+wordlist.begin(),temp);
			return;
		}
	}
	wordlist.push_back(temp);
}

//skriver ut tabellen
static void print_table(const vector<word_entry>& wordlist)
{
	cout<<setw(8)<<"Ord"<<setw(10)<<"Antal\n\n";
	for (unsigned long element=0;element<wordlist.size();element++)
	{
		int extraspace;
		extraspace=(int)log10(wordlist.at(element).count);
		
		cout<<setw(8)<<wordlist.at(element).word<<setw(4+extraspace)<<wordlist.at(element).count<<"\n";
	}
}

int main()
{	
	string input;
	vector <word_entry> wordlist;
	while (cin>>input)
	{
		transform(input.begin(),input.end(),input.begin(),::tolower);
		insert(wordlist,input);	
	}
	print_table(wordlist);
  	return 0;
}
