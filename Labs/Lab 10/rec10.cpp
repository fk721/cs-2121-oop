// Fahmid Kamal
// rec10, More Pointers
// This program models an ochrestra 
// with musicians
// that play instruments

#include <iostream>
#include <vector>
using namespace std;

// INSTRUMENT HIEARCHY

class Instrument {
public:
	virtual void makeSound() const = 0;
	virtual void playSound() const = 0;
};

void Instrument::makeSound() const { cout << "To make a sound..."; }

class Brass : public Instrument {
public:
	Brass(const unsigned size) : Instrument(), size(size) {};
	virtual void makeSound() const = 0;
	virtual void playSound() const = 0;
private:
	unsigned size;
};

void Brass::makeSound() const {
	Instrument::makeSound();
	cout << "blow on mouthpiece of size " << size << endl;
}


class Trumpet : public Brass {
public:
	Trumpet(const unsigned size) : Brass(size) {}
	virtual void makeSound() const {
		Brass::makeSound();
	}
	virtual void playSound() const {
		cout << "Toot";
	}
};

class Trombone : public Brass {
public:
	Trombone(const unsigned size) : Brass(size) {}
	//using Brass::makeSound();
	virtual void makeSound() const {
		Brass::makeSound();
	}
	virtual void playSound() const {
		cout << "Blat";
	}
};

class String : public Instrument {
public:
	String(const unsigned pitch) : Instrument(), pitch(pitch) {}
	virtual void makeSound() const = 0;
	virtual void playSound() const = 0;
private:
	unsigned pitch;
};

void String::makeSound() const {
	Instrument::makeSound();
	cout << "bow a string with pitch " << pitch << endl;
}

class Violin : public String {
public:
	Violin(const unsigned pitch) : String(pitch) {}
	void makeSound() const {
		String::makeSound();
	}
	virtual void playSound() const {
		cout << "Screech";
	}
};

class Cello : public String {
public:
	Cello(const unsigned pitch) : String(pitch) {}
	void makeSound() const {
		String::makeSound();
	}
	virtual void playSound() const {
		cout << "Squawk";
	}
};

class Percussion : public Instrument {
public:
	virtual void makeSound() const = 0;
	virtual void playSound() const = 0;
};

void Percussion::makeSound() const {
	Instrument::makeSound();
	cout << "hit me!" << endl;
}

class Drum : public Percussion {
public:
	void makeSound() const {
		Percussion::makeSound();
	}
	virtual void playSound() const {
		cout << "Boom";
	}
};

class Cymbal : public Percussion {
public:
	void makeSound() const {
		Percussion::makeSound();
	}
	virtual void playSound() const {
		cout << "Crash";
	}
};

// END INSTRUMENT HIEARCHY


class Musician {
public:
	Musician() : instr(nullptr) {}

	void acceptInstr(Instrument* instPtr) { instr = instPtr; }

	Instrument* giveBackInstr() {
		Instrument* result(instr);
		instr = nullptr;
		return result;
	}

	void testPlay() const {
		if (instr) instr->makeSound();
		else cerr << "have no instr\n";
	}
	Instrument* getInstrument() const {
		return instr;
	}

private:
	Instrument* instr;
};

// MILL 

class MILL {
public:
	// Default constructor
	MILL() : inventory(1, nullptr) {}

	void dailyTestPlay() const {
		for (size_t i = 0; i < inventory.size(); ++i) {
			if (inventory[i] != nullptr) {
				inventory[i]->makeSound();
			}
		}
	}

	void receiveInstr(Instrument& instr) {
		// Test the instrument
		instr.makeSound();
		// Add the instrument to the inventory
		for (size_t i = 0;  i < inventory.size(); ++i) {
			if (inventory[i] == nullptr) {
				inventory[i] = &instr;
				return;
			}
		}
		// Did not have space, call carpenters to add to end of bin
		inventory.push_back(&instr);
	}

	Instrument* loanOut() {
		for (size_t i = 0; i < inventory.size(); ++i) {
			if (inventory[i] != nullptr) {
				Instrument* resInstr = inventory[i];
				inventory[i] = nullptr;
				return resInstr;
			}
		}
		return nullptr;
	}

private:
	vector<Instrument*> inventory;
};

class Orch {
public:
	Orch() : band(25, nullptr) {}
	void addPlayer(Musician& player) {
		for (size_t i = 0; i < band.size(); ++i) {
			if (band[i] == nullptr) {
				band[i] = &player;
				break;
			}
		}
	}
	void play() const {
		for (size_t i = 0; i < band.size(); ++i) {
			if (band[i] != nullptr && band[i]->getInstrument() != nullptr) {
				band[i]->getInstrument()->playSound();
			}
		}
		cout << endl;
	}
private:
	vector <Musician*> band;
};

// PART TWO
int main() {
	// The initialization phase

	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone(4);
	Trumpet trpt(12);
	Violin violin(567);

	MILL mill;
	mill.receiveInstr(trpt);
	mill.receiveInstr(violin);
	mill.receiveInstr(tbone);
	mill.receiveInstr(drum);
	mill.receiveInstr(cello);
	mill.receiveInstr(cymbal);

	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;

	Orch orch;

	// THE SCENARIO

	//Bob joins the orchestra without an instrument.
	orch.addPlayer(bob);

	//The orchestra performs
	cout << "orch performs\n";
	orch.play();
	cout << "orch finishes performance\n";

	//Sue gets an instrument from the MIL2 and joins the orchestra.
	sue.acceptInstr(mill.loanOut());
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr(mill.loanOut());

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr(mill.loanOut());
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr(*ralph.giveBackInstr());

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr(mill.loanOut());
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
	cout << "orch finishes performance\n";
//
	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
	cout << "orch finishes performance\n";

	// bob gets an instrument from the MIL2
	bob.acceptInstr(mill.loanOut());

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
	cout << "orch finishes performance\n";

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
	cout << "orch finishes performance\n";
}

//// PART ONE
//int main() {
//
//	 cout << "Define some instruments ----------------------------------------\n";
//	 Drum drum;
//	 Cello cello(673);
//	 Cymbal cymbal;
//	 Trombone tbone(4);
//	 Trumpet trpt(12) ;
//	 Violin violin(567) ;
//	 /*drum.makeSound();
//	 cello.makeSound();
//	 tbone.makeSound();
//	 trpt.makeSound();
//	 violin.makeSound();*/
//
//	// // use the debugger to look at the mill
//	 cout << "Define the MILL ------------------------------------------------\n";
//	 MILL mill;
//
//	 cout << "Put the instruments into the MILL ------------------------------\n";
//	 mill.receiveInstr(trpt);
//	 mill.receiveInstr(violin);
//	 mill.receiveInstr(tbone);
//	 mill.receiveInstr(drum);
//	 mill.receiveInstr(cello);
//	 mill.receiveInstr(cymbal);
//
//	 cout << "Daily test -----------------------------------------------------\n";
//	 cout << endl;
//	 cout << "dailyTestPlay()" << endl;
//	 mill.dailyTestPlay();
//	 cout << endl;
//
//	 cout << "Define some Musicians-------------------------------------------\n";
//	 Musician harpo;
//	 Musician groucho;
//
//	 cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
//	 groucho.testPlay();	
//	 cout << endl;
//	 groucho.acceptInstr(mill.loanOut());
//	 cout << endl;
//	 groucho.testPlay();
//	 cout << endl;
//	 cout << "dailyTestPlay()" << endl;
//	 mill.dailyTestPlay();
//
//	 cout << endl << endl;
//
//	 groucho.testPlay();	
//	 cout << endl;
//	 mill.receiveInstr(*groucho.giveBackInstr());
//	 harpo.acceptInstr(mill.loanOut());
//	 groucho.acceptInstr(mill.loanOut());
//	 cout << endl;
//	 groucho.testPlay();
//	 cout << endl;
//	 harpo.testPlay();
//	 cout << endl;
//	 cout << "dailyTestPlay()" << endl;
//	 mill.dailyTestPlay();
//
//	 cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----------\n";
//
//	 // fifth
//	 mill.receiveInstr(*groucho.giveBackInstr());
//	 cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
//	 mill.receiveInstr(*harpo.giveBackInstr());
//
//
//	 cout << endl;
//	 cout << "dailyTestPlay()" << endl;
//	 mill.dailyTestPlay();
//	 cout << endl;
//
//	 cout << endl;
//
//}
