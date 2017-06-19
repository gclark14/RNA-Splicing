#include "RNATranslator.h"
#include "RNASplicer.h"
int main(){
	ifstream fin;
	fin.open("rosalind_splc.txt");
	RNASplicer *splicer = new RNASplicer(fin);	
	splicer->splice();
	RNATranslator *translator = 
		new RNATranslator(splicer->getSplicedDna());
	translator->translate();
	translator->save();
	return 0;
}
