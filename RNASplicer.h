#include "Fasta.h"
class RNASplicer{
private:
	vector<string> introns;
	string splicedDna;		

	void setIntrons(){
		for(int i = 1; i < fasta.table.size()-1; i++){
			introns.push_back(fasta.getDna(i));
		}
	}

	void removeIntrons(){
		string original = fasta.getDna(0);
		for(int i = 0; i < introns.size(); i++){ // for each intron 
			for(int j = 0; j < original.length(); j++){ // for each nucleotide in original
				if(introns.at(i).at(0) == original.at(j) and (j + introns.at(i).length()) <= original.length()){
					bool isSubstring = true;
					for(int k = 0; k < introns.at(i).length(); k++){
						if(original.at(j+k) != introns.at(i).at(k)){
							isSubstring = false;
							break;
						}
					}
					if(isSubstring){
						original.erase(j,introns.at(i).size());
					}
				}
			}
		}
		splicedDna = original;
	}

	void convertDnaToRna(){
		for(int i = 0; i < fasta.table.size(); i++){
			string temp = fasta.getDna(i);
			for(int j = 0; j < fasta.getDna(i).length(); j++){
				if(temp.at(j) == 'T'){
					temp.replace(j,1,"U");
				}
			}
			fasta.setDna(i,temp);
		}
	}

public:
	Fasta fasta;
	RNASplicer(ifstream& fin){
		fasta.populateTable(fin);
		convertDnaToRna();
	}

	void printIntrons(){
		for(int i = 0; i < introns.size(); i++){
			cout << "intron: " << introns.at(i) << '\n';
		}
	}

	void splice(){
		setIntrons();
		removeIntrons();
	}

	string getSplicedDna(){ return splicedDna; }

};


