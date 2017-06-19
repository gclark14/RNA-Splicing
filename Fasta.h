#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Fasta{
private:
	string id;
	string dna;

	void resetInputFileStream(ifstream& fin){
		fin.clear();
		fin.seekg(0, std::ios::beg);
	}

public:
	Fasta(){}	
	Fasta(ifstream& fin){
		populateTable(fin);
	}

	vector<Fasta> table;

	string getId(int index){
		return table.at(index).id;
	}

	string getDna(int index){
		return table.at(index).dna;
	}

	string getId(){ return id; } 

	string getDna() { return dna; }
	
	void setDna(int index, string dna){
		table.at(index).dna = dna;
	}

	void setId(int index, string id){
		table.at(index).id = id;
	}

	vector<Fasta> getTable(){ return table; } 

	int getFastaCount(ifstream& fin){
		int fastaCount = 0;
		char check;
		while(fin){
			fin >> check;
			if(check == '>')
				fastaCount++;
		}
		return fastaCount;
	}

	void populateTable(ifstream& fin){
		int max = getFastaCount(fin);
		resetInputFileStream(fin);
		for(int i = 0; i <= max; i++){
			Fasta f;
			string s;
			getline(fin,f.id);
			while(fin.peek() != '>' and fin){ 
				char c = fin.peek();
				string temp;
				getline(fin,temp);
				f.dna += temp;
			}
			table.push_back(f);
		}
	}

	void printTable(){
		for_each(table.begin(), table.end(), printFasta);
	}

	static void printFasta(Fasta f){
		cout << '\n' << f.id;
		cout << '\n' << f.dna << '\n';
	}
};
