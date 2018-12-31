// Fahmid Kamal
// Fk786
// Rec 01

// The following program implements Conway's Game of Life when given an initial population
// Dashes for dead cells and asterisks for live ones

# include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
	ifstream ifs("life.txt"); // Opens File
	if (!ifs) { // Checks if file opened successfully
		cerr << "Could not open the file." << endl;
		exit(1);
	}
	string line;
	vector <string> vectorOfLives;
	while ((getline(ifs, line))) { // Pushes each string of the file into the vector
		vectorOfLives.push_back(line);
	}

	cout << "Starting Generation:" << endl << endl;
	for (size_t i = 0; i < vectorOfLives.size(); ++i) { // Prints initial generation
		for (size_t u = 0; u < vectorOfLives[i].size(); ++u) {
			cout << vectorOfLives[i][u];
		}
		cout << endl;	
	}
	cout << endl;

	for (int currGenNum = 1; currGenNum <= 10; ++currGenNum) {
		vector <string> newVectorOfLives;
		for (size_t i = 0; i < vectorOfLives.size(); ++i) { // For loop will traverse through rows
			string line;
			for (size_t u = 0; u < vectorOfLives[i].size(); ++u) { // Second For loop will traverse through columns
				int numOfLiving = 0;
				if (u + 1 < vectorOfLives[i].size()) { // Checks to see if neighbor to right center exists
					if (vectorOfLives[i][u + 1] == '*') {
						++numOfLiving;
					}			
				}
				if (u > 0) { // Checks to see if neighbor to left center exists
					if (vectorOfLives[i][u - 1] == '*') {
						++numOfLiving;
					}					
				}
				if (i > 0) { // Checks to see if neighbor to top center exists
					if (vectorOfLives[i - 1][u] == '*') {
						++numOfLiving;
					}			
				}
				if (i + 1 < vectorOfLives.size()) { // Checks to see if neighbor to bottom center exists
					if (vectorOfLives[i + 1][u] == '*') {
						++numOfLiving;
					}	
				}
				if (i > 0 && u + 1 < vectorOfLives[i].size()) { // Checks to see if neighbor to top right exists
					if (vectorOfLives[i - 1][u + 1] == '*') {
						++numOfLiving;
					}	
				}
				if (i > 0 && u > 0) { // Checks to see if neighbor to top left exists
					if (vectorOfLives[i - 1][u - 1] == '*') {
						++numOfLiving;
					}	
				}
				if (i + 1 < vectorOfLives.size() && u + 1 < vectorOfLives[i].size()) { // Checks to see if neighbor to bottom right exists
					if (vectorOfLives[i + 1][u + 1] == '*') {
						++numOfLiving;
					}	
				}
				if (i + 1 < vectorOfLives.size() && u >0) { // Checks to see if neighbor to bottom left exists
					if (vectorOfLives[i + 1][u - 1] == '*') {
						++numOfLiving;
					}	
				}
				if (vectorOfLives[i][u] == '*') { // Curr cell is alive
					if (numOfLiving == 2 || numOfLiving == 3) {
						line = line + "*";
					}
					else { 
						line = line + "-";
					}
				}
				else { // Curr cell is dead
					if (numOfLiving == 3) {
						line = line + "*";
					}
					else {
						line = line + "-";
					}
				}

			}
			newVectorOfLives.push_back(line); // New 2d-vector is created line by line
			
		}
		vectorOfLives = newVectorOfLives; // Old 2d vector is replaced with new one
		cout << "Generation " << currGenNum << ":" << endl;
		for (size_t i = 0; i < vectorOfLives.size(); ++i) { // Prints subsequent generation
			for (size_t u = 0; u < vectorOfLives[i].size(); ++u) {
				cout << vectorOfLives[i][u];
			}
			cout << endl;
		}
		cout << endl;
	}
	ifs.close();
}
