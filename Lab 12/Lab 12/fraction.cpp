#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

#include "fraction.h"


fraction::fraction(int Numerator, int Denominator, bool reduceInput)
{
	numerator = Numerator;
	denominator = Denominator;

	if(reduceInput) reduce();
}

void fraction::reduce()	//Do this bit lmao
{
	std::vector<int> primeFactors {2, 3, 5, 7, 11, 13};

	for(auto iter = primeFactors.begin(); iter != primeFactors.end(); iter++)
	{
		int factor = *iter;

		if(numerator >= factor && denominator >= factor)
		{

			while(numerator%factor == 0 && denominator%factor == 0)	//If we divide the top and bottom by 'factor' and the remainder for both is 0, we can factor 'factor' out of the fraction
			{

				//This is handled as individual elements instead of doing it as a fraction / int because we would end up in an infinite loop otherwise
				numerator /= factor;
				denominator /= factor;
			}
		}
		else break;
	}
}

fraction fraction::getInverse()
{
	return fraction(denominator, numerator, false);
}

void fraction::print()
{
	cout << "(" << getNumerator() << "/" << getDenominator() << ")" << endl;
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

fraction fraction::operator/=(fraction other)
{
	(*this) = (*this) / other;
	return *this;
}

fraction fraction::operator/(int  other)
{
	return fraction(numerator, denominator * other);
}

std::pair<fraction, fraction> fraction::convertToCommonDenominator(fraction first, fraction second)
{
	{
		fraction newFirst = fraction(first.getNumerator() * second.getDenominator(), first.getDenominator() * second.getDenominator(), false);
		fraction newSecond = fraction(second.getNumerator() * first.getDenominator(), second.getDenominator() * first.getDenominator(), false);
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