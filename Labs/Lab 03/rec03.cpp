# include <iostream>
# include <vector>
# include <string>
# include <cstdlib>
# include <ctime>
using namespace std;


struct Tile {
	Tile(): bomb(false), isVisible(false), surroundingBombs(0) {}
	bool bomb;
	bool isVisible;
	int surroundingBombs;
};

class Minesweeper {
public:
	Minesweeper() {
		for (int x = 0; x < ROWS; ++x) {
			vector < Tile > currTileVector;
			for (int y = 0; y < COLS; ++y) {
				Tile currTile;
				currTileVector.push_back(currTile);
			}
			minesweeperVectorBoard.push_back(currTileVector);
		}
		srand(time(NULL));

		for (int i = 0; i < BOMB_PROBABILITY; ++i) { // 10 of thoese empty tiles will be bombs, randomly selected
			int randX = rand() % ROWS;
			int randY = rand() % COLS;
			if (!minesweeperVectorBoard[randX][randY].bomb) {
				minesweeperVectorBoard[randX][randY].bomb = true;
				numOfBombs += 1;
			}
		}
		for (int x = 0; x < ROWS; ++x) {
			for (int y = 0; y < COLS; ++y) {
				if (minesweeperVectorBoard[x][y].bomb) { // Tile is a bomb
					minesweeperVectorBoard[x][y].surroundingBombs = -1;
				}
				else { // Tile is not a bomb, must check 8 surrounding neighbors
					minesweeperVectorBoard[x][y].bomb = false;
					int numOfSurroundingBombs = 0;
					if (x < ROWS - 1) { // bottom  neighbor
						if (minesweeperVectorBoard[x + 1][y].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (x >= 1) { // top neighbor
						if (minesweeperVectorBoard[x - 1][y].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (y < COLS - 1) { // right neighbor
						if (minesweeperVectorBoard[x][y + 1].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (y >= 1) { //left neighbor
						if (minesweeperVectorBoard[x][y - 1].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (x >= 1 && y < COLS - 1) { // top right
						if (minesweeperVectorBoard[x - 1][y + 1].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (x >= 1 && y >= 1) { // top left
						if (minesweeperVectorBoard[x - 1][y - 1].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (x < ROWS - 1 && y >= 1) { // bottom left
						if (minesweeperVectorBoard[x + 1][y - 1].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					if (x < ROWS - 1 && y < COLS - 1) { // bottom right
						if (minesweeperVectorBoard[x + 1][y + 1].bomb) {
							numOfSurroundingBombs += 1;
						}
					}
					minesweeperVectorBoard[x][y].surroundingBombs =
					numOfSurroundingBombs;
				}
			}
		}
	}
	void display(bool isDone) {
		for (int x = 0; x < ROWS; ++x) {
			for (int y = 0; y < COLS; ++y) {
				if (isDone == true) {
					if (minesweeperVectorBoard[x][y].bomb == true) {
						cout << "B" << " ";
					}
					else {
						cout << minesweeperVectorBoard[x][y].surroundingBombs << " ";
					}
				}
				else {
					if (minesweeperVectorBoard[x][y].bomb == true) {
						cout << "-" << " ";
					}
					else {
						if (minesweeperVectorBoard[x][y].isVisible == true) {
							cout << minesweeperVectorBoard[x][y].surroundingBombs << " ";
						}
						else {
							cout << "-" << " ";
						}
					}
				}
			}
			cout << endl;
		}
		cout << "Tiles Played: " << tilesPlayed << endl << endl;
	}
	bool validRow(int row) const {
		if (row >= 0 && row < ROWS) {
			return true;
		}
		else {
			return false;
		}
	}
	bool validCol(int col) const {
		if (col >= 0 && col < COLS) {
			return true;
		}
		return false;
	}

	bool isVisible(int row, int col) {
		if (minesweeperVectorBoard[row][col].isVisible == true) {
			return true;
		}
		return false;
	}

	bool play(int row, int col) {
		if (minesweeperVectorBoard[row][col].bomb == true) {
			return false;
		}
		if (minesweeperVectorBoard[row][col].surroundingBombs != 0) {
			minesweeperVectorBoard[row][col].isVisible = true;
			tilesPlayed += 1;
		}
		else {
			checkSurroundingNeighbors(minesweeperVectorBoard, row, col);
			minesweeperVectorBoard[row][col].isVisible = true;
		}
		return true;
	}

	void checkSurroundingNeighbors(vector < vector < Tile> >& vectorTiles, int x, int y) {
		if (vectorTiles[x][y].bomb == true) {
			return;
		}
		if (vectorTiles[x][y].isVisible == true) {
			return;
		}
		if (vectorTiles[x][y].surroundingBombs != 0) {
			return;
		}
		vectorTiles[x][y].isVisible = true;
		tilesPlayed += 1;
		if (x < ROWS - 1) { // bottom  neighbor
			if (vectorTiles[x + 1][y].surroundingBombs == 0
				&& vectorTiles[x + 1][y].isVisible == false) {
				//vectorTiles[x + 1][y].isVisible = true;
				//tilesPlayed += 1;
				checkSurroundingNeighbors(vectorTiles, x + 1, y);
			}
			else if (vectorTiles[x + 1][y].surroundingBombs != 0
				&& vectorTiles[x + 1][y].isVisible == false) {
				vectorTiles[x + 1][y].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (x >= 1) { // top neighbor
			if (vectorTiles[x - 1][y].surroundingBombs == 0
				&& vectorTiles[x - 1][y].isVisible == false) {
				//vectorTiles[x-1][y].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x - 1, y);
			}
			else if (vectorTiles[x - 1][y].surroundingBombs != 0
				&& vectorTiles[x - 1][y].isVisible == false) {
				vectorTiles[x - 1][y].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (y < COLS - 1) { // right neighbor
			if (vectorTiles[x][y + 1].surroundingBombs == 0
				&& vectorTiles[x][y + 1].isVisible == false) {
				//vectorTiles[x][y+1].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x, y + 1);
			}
			else if (vectorTiles[x][y + 1].surroundingBombs != 0
				&& vectorTiles[x][y + 1].isVisible == false) {
				vectorTiles[x][y + 1].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (y >= 1) { //left neighbor
			if (vectorTiles[x][y - 1].surroundingBombs == 0
				&& vectorTiles[x][y - 1].isVisible == false) {
				//vectorTiles[x][y-1].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x, y - 1);
			}
			else if (vectorTiles[x][y - 1].surroundingBombs != 0
				&& vectorTiles[x][y - 1].isVisible == false) {
				vectorTiles[x][y - 1].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (x >= 1 && y < COLS - 1) { // top right
			if (vectorTiles[x - 1][y + 1].surroundingBombs == 0
				&& vectorTiles[x - 1][y + 1].isVisible == false) {
				//vectorTiles[x-1][y+1].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x - 1, y + 1);
			}
			else if (vectorTiles[x - 1][y + 1].surroundingBombs != 0
				&& vectorTiles[x - 1][y + 1].isVisible == false) {
				vectorTiles[x - 1][y + 1].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (x >= 1 && y >= 1) { // top left
			if (vectorTiles[x - 1][y - 1].surroundingBombs == 0
				&& vectorTiles[x - 1][y - 1].isVisible == false) {
				//vectorTiles[x-1][y-1].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x - 1, y - 1);
			}
			else if (vectorTiles[x - 1][y - 1].surroundingBombs != 0
				&& vectorTiles[x - 1][y - 1].isVisible == false) {
				vectorTiles[x - 1][y - 1].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (x < ROWS - 1 && y >= 1) { // bottom left
			if (vectorTiles[x + 1][y - 1].surroundingBombs == 0
				&& vectorTiles[x + 1][y - 1].isVisible == false) {
				//vectorTiles[x+1][y-1].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x + 1, y - 1);
			}
			else if (vectorTiles[x + 1][y - 1].surroundingBombs != 0
				&& vectorTiles[x + 1][y - 1].isVisible == false) {
				vectorTiles[x + 1][y - 1].isVisible = true;
				tilesPlayed += 1;
			}
		}
		if (x < ROWS - 1 && y < COLS - 1) { // bottom right
			if (vectorTiles[x + 1][y + 1].surroundingBombs == 0
				&& vectorTiles[x + 1][y + 1].isVisible == false) {
				//vectorTiles[x+1][y+1].isVisible = true;
				//tilesPlayed +=1;
				checkSurroundingNeighbors(vectorTiles, x + 1, y + 1);
			}
			else if (vectorTiles[x + 1][y + 1].surroundingBombs != 0
				&& vectorTiles[x + 1][y + 1].isVisible == false) {
				vectorTiles[x + 1][y + 1].isVisible = true;
				tilesPlayed += 1;
			}
		}
		return;
	}

	bool done() {
		int totalTiles = ROWS * COLS;
		if (tilesPlayed + numOfBombs == totalTiles) {
			return true;
		}
		return false;
	}

private:
	vector <vector < Tile > > minesweeperVectorBoard; // 0x0 vector
	int numOfBombs = 0;
	int tilesPlayed = 0;
	const int ROWS = 10;
	const int COLS = 10;
	const int BOMB_PROBABILITY = (ROWS * COLS) / 10;

};

int main() {
	Minesweeper sweeper;
	// Continue until only invisible cells are bombs
	//sweeper.display(true);
	while (!sweeper.done()) {
		sweeper.display(false); // display board without bombs

		int row_sel = -1, col_sel = -1;
		while (row_sel == -1) {
			// Get a valid move
			int r, c;
			cout << "row? ";
			cin >> r;
			r = r - 1;
			if (!sweeper.validRow(r)) {
				cout << "Row out of bounds\n";
				continue;
			}
			cout << "col? ";
			cin >> c;
			c = c - 1;
			if (!sweeper.validCol(c)) {
				cout << "Column out of bounds\n";
				continue;
			}
			if (sweeper.isVisible(r, c)) {
				cout << "Square already visible\n";
				continue;
			}
			if (sweeper.validRow(r) && sweeper.validCol(c)) {
				row_sel = r;
				col_sel = c;
			}
		}
		// Set selected square to be visible. May effect other cells.
		if (!sweeper.play(row_sel, col_sel)) {
			cout << "Sorry, you died..\n";
			sweeper.display(true); // Final board with bombs shown
			exit(0);
		}
	}
	// Ah! All invisible cells are bombs, so you won!
	cout << "You won!!!!\n";
	sweeper.display(true); // Final board with bombs shown
}
