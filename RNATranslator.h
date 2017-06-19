#include "CodonMap.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class RNATranslator{
private:
	string rna;	
	string protein;

public:

	RNATranslator(string rna){
		this->rna = rna;
	}
	
	RNATranslator(){ protein = rna = ""; }

	void setRna(ifstream& fin){
		while(fin){
			string temp;
			getline(fin,temp);
			rna += temp;
		}
	}

	string getRna(){ return rna; }

	void translate(){
		string codon = "";
		int count = 1;
		for(int i = 0; i < rna.length(); i++){
			codon += rna.at(i);
			if(count == 3){
				codonMapIterator = codonMap.find(codon);
				if(codonMapIterator->second != "Stop")
					protein += codonMapIterator->second;
				codon = "";
				count = 0;
			}
			count++;
		}
	}

	void save(){
		ofstream fout;
		fout.open("save.txt");
		fout << protein << '\n';
		fout.close();
	}

};
