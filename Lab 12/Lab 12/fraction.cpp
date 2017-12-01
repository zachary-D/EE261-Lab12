//*******************************************************

// Implementation file fraction.cpp implements the member 
// functions of class fraction.


#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

#include "fraction.h"


fraction::fraction(int Numerator, int Denominator, bool reduceInput = true)
{
	numerator = Numerator;
	denominator = Denominator;

	if(reduceInput) reduce();
}

void fraction::reduce()	//Do this bit lmao
{

}

fraction fraction::getInverse()
{
	return fraction(denominator, numerator, false);
}

fraction fraction::operator+(fraction other)
{
	//Find LCM of denominators, and convert fractions to same-base
	std::pair<fraction, fraction> LCM = convertToCommonDenominator(*this, other);
	
	//Add numerators
	//Return output
	return fraction(LCM.first.getNumerator() + LCM.second.getNumerator(), LCM.first.getDenominator());
}

fraction fraction::operator-(fraction other)
{
	//Find LCM of denominators, and convert fractions to same-base
	std::pair<fraction, fraction> LCM = convertToCommonDenominator(*this, other);

	//Subtract numerators
	//Return output
	return fraction(LCM.first.getNumerator() - LCM.second.getNumerator(), LCM.first.getDenominator());
}

fraction fraction::operator*(fraction other)
{
	return fraction(numerator * other.getNumerator(), denominator * other.getDenominator());
}

fraction fraction::operator*(int other)
{
	return fraction(numerator * other, denominator);
}

fraction fraction::operator/(fraction  other)
{
	return (*this) * other.getInverse();
}

fraction fraction::operator/(int  other)
{
	return fraction(numerator, denominator * other);
}

std::pair<fraction, fraction> fraction::convertToCommonDenominator(fraction first, fraction second)
{
	{
		fraction newFirst = first * second.getDenominator();
		fraction newSecond = second * first.getDenominator();
		return std::pair<fraction, fraction>(newFirst, newSecond);
	}


	//This part isn't used currently, but if this system is used it will factor the denominators as small as they can go,
	//then sort them least -> greatest, then identify what each will need to be multipied by in order to get a common denominator
	/*{
	int base1 = first.getDenominator();
	int base2 = second.getDenominator();

	//Breaks 'value' down into its smallest components (only uses factors
	auto factor = [] (int value)
	{

	};
	}*/
}



int main() {
	fraction a = fraction(1, 2);
	fraction b = fraction(1, 4);
	cin.ignore();
}
