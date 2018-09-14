// Fahmid Kamal
// Fk786
// rec02

// The following programs takes a file containing compounds and their formula
// and sorts them based on the number of carbon atoms they have


# include <iostream>
# include <fstream>
# include <vector>
# include <string>
using namespace std;

struct Formula {
	vector <string> name;
	int numOfCarbon;
	int numOfHydrogen;
};

void fillFormulaVector(ifstream& ifs, vector <Formula>& vf);
void enterFileName(ifstream& ifs);
void sortFormulaVector(vector <Formula>& vc);
void displayFormulaVector(vector <Formula>& vf);

int main() {
	ifstream ifs;
	vector < Formula > vectorOfFormulas;
	enterFileName(ifs);
	fillFormulaVector(ifs, vectorOfFormulas);
	sortFormulaVector(vectorOfFormulas);
	displayFormulaVector(vectorOfFormulas);
}

void fillFormulaVector(ifstream& ifs, vector <Formula>& vf) {
	string formulaName;
	int carbon;
	int hydrogen;
	char c;
	char h;
	while (ifs >> formulaName >> c >> carbon >> h >> hydrogen) {
		Formula f;
		bool seeRepeat = false;
		for (size_t i = 0; i < vf.size(); ++i) {
			if (vf[i].numOfCarbon == carbon && vf[i].numOfHydrogen == hydrogen 
				&& i < vf.size()) {
				vf[i].name.push_back(formulaName);
				seeRepeat = true;
			}
		}

		if (seeRepeat == false) {
			f.name.push_back(formulaName);
			f.numOfCarbon = carbon;
			f.numOfHydrogen = hydrogen;
			vf.push_back(f);
		}
	}
	ifs.close();
}


void enterFileName(ifstream& ifs) {
	string fileName;
	cout << "Please enter the file name: " << endl;
	cin >> fileName;
	ifs.clear();
	ifs.open(fileName);
	while (!ifs) {
		cout << "Please enter a valid file name: " << endl;
		cin >> fileName;
		ifs.clear();
		ifs.open(fileName);
	}
}

void sortFormulaVector(vector <Formula>& vc) {
	for (size_t i = 0; i < vc.size(); ++i) {
		for (size_t u = 0; u + 1 < vc.size(); ++u) {
			if (vc[u].numOfCarbon > vc[u + 1].numOfCarbon) {
				Formula temp;
				temp = vc[u];
				vc[u] = vc[u + 1];
				vc[u + 1] = temp;
			}
			if (vc[u].numOfCarbon == vc[u + 1].numOfCarbon) {
				if (vc[u].numOfHydrogen > vc[u + 1].numOfHydrogen) {
					Formula temp;
					temp = vc[u];
					vc[u] = vc[u + 1];
					vc[u + 1] = temp;
				}
			}
		}
	}
}

void displayFormulaVector(vector <Formula>& vf) {
	for (size_t i = 0; i < vf.size(); ++i) {
		cout << "C" << vf[i].numOfCarbon << "H" <<
			vf[i].numOfHydrogen << ' ';
		for (size_t u = 0; u < vf[i].name.size(); ++u) {
			cout << vf[i].name[u] << ' ';
		}
		cout << endl;
	}
}