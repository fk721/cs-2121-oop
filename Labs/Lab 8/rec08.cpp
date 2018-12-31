/*	Fahmid Kamal
	fk786
	rec08
	Implementing a class for rational numbers
 */

#include <iostream>
using namespace std;

class Rational {
	friend ostream& operator<<(ostream& os, const Rational& rhs);
	friend istream& operator>>(istream& is, Rational& rhs);
	friend bool operator==(const Rational& rhs, const Rational& lhs);
	friend bool operator<(const Rational& rhs, const Rational& lhs);
public:
	Rational(int numInput = 0, int denInput = 1) {
		simplifyNumDen(numInput, denInput);
	}

	Rational& operator+=(const Rational& rhs) {
		num = num * rhs.den + rhs.num * den;
		den = rhs.den * den;
		simplifyNumDen(num, den); 
		return *this;
	}
	// pre-increment, does not make a copy, returns ME
	// return by reference
	Rational& operator++() {
		Rational dummyOne(1);
		*this += dummyOne;
		return *this;
	}
	// post-increment, makes a copy, then increments
	Rational operator++(int dummy) {
		Rational original(*this);
		Rational dummyOne(1);
		*this += dummyOne;
		return original;
	}
	explicit operator bool() const {
		return num;
	}
private:
	int greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}
		return x;
	}

	void simplifyNumDen(int numInput, int denInput) { // simplifies
		int div = greatestCommonDivisor(numInput, denInput);
		num = numInput / div;
		den = denInput / div;
		if (denInput < 0) {
			num *= -1;
			den *= -1;
		}
	}
	int num;
	int den;
};

// Friends

	// output operator
ostream& operator<<(ostream& os, const Rational& rhs) {
	os << rhs.num << '/' << rhs.den;
	return os;
}
	// input operator
istream& operator>>(istream& is, Rational& rhs) {
	char c = '/';
	is >> rhs.num >> c >> rhs.den;
	return is;
}
	// == operator
bool operator==(const Rational& rhs, const Rational& lhs) {
	return rhs.num == lhs.num && rhs.den == lhs.den;
}
	// < operator
bool operator<(const Rational& rhs, const Rational& lhs) {
	return (rhs.num * lhs.den < lhs.num * rhs.den); // cross multiply
}

// Non-friends
	// + operator
Rational operator+(const Rational& rhs, const Rational& lhs) {
	Rational res(rhs); // 0 + rhs = rhs
	res += lhs;
	return res;
}
	// != operator
bool operator!=(const Rational& rhs, const Rational& lhs) {
	return !(rhs == lhs);
}
	// pre-increment, does not make a copy, returns ME
	// return by reference
Rational& operator--(Rational& rhs) {
	Rational dummyOne(-1);
	rhs += dummyOne;
	return rhs;
}
	// post-increment, makes a copy, then increments
	// a-- will give you the orignal value of a, but it modifies a
Rational operator--(Rational& rhs, int dummy) {
	Rational original(rhs);
	Rational dummyOne(-1);
	rhs += dummyOne;
	return original;
}
bool operator>(const Rational& rhs, const Rational&lhs) {
	return (lhs < rhs);
}
bool operator <=(const Rational & rhs, const Rational& lhs) {
	return (lhs < rhs || lhs == rhs);
}

bool operator >=(const Rational & rhs, const Rational& lhs) {
	return (lhs > rhs || lhs == rhs);
}

// main

int main() {
	Rational twoThirds(2, 3);
	cout << twoThirds << endl;

	Rational a, b;
	cout << "Input two rational numbers.\n";
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	Rational one(1);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "one = " << one << endl;
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;

	// Implement as non-member, but not a friend
	cout << "a + one: " << (a + one) << endl;
	cout << "a == one: " << boolalpha << (a == one) << endl;

	// How does this manage to work?
	// It does NOT require writing another == operator. 


	cout << "1 == one: " << boolalpha << (one == 1) << endl;

	// Do not implement as friend.
	cout << "a != one: " << boolalpha << (a != one) << endl;

	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;
	cout << "++ ++a = " << (++ ++a) << endl;
	cout << "a = " << a << endl;
	cout << "-- --a = " << (-- --a) << endl;
	cout << "a = " << a << endl;

	cout << "a++ ++ = " << (a++ ++) << endl;
	cout << "a = " << a << endl;

	// even though the above example, (a++ ++), compiled, the
	// following shouldn't.
	// but some compiler vendors might let it...  is your compiler
	// doing the right thing?
	// cout << "a-- -- = " << (a-- --) << endl;
	// cout << "a = " << a << endl;


	if (Rational(1)) {
		cout << "1 is true" << endl;
	}
	else {
		cout << "1 is false" << endl;
	}
	if (Rational(0)) {
		cout << "0 is true" << endl;
	}
	else {
		cout << "0 is false" << endl;
	}
}