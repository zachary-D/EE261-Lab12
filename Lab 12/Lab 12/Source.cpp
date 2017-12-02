#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "fraction.h"

int main() {
	cout << "1/2 + 1/4 = ";
	(fraction(1, 2) + fraction(1, 4)).print();

	cout << "1/2 - 1/4 = ";
	(fraction(1, 2) - fraction(1, 4)).print();

	cout << "1/2 * 1/2 = ";
	(fraction(1, 2) * fraction(1, 2)).print();

	cout << "1/2 / 1/2 = ";
	(fraction(1, 2) / fraction(1, 2)).print();


	cin.ignore();
}