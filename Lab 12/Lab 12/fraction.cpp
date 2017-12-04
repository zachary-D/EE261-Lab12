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

	if(denominator == 0) throw "Numerator cannot be 0!";

	if(denominator < 0)		//If the denominator is a negative, move the negative up to the top (standard form).  This also will handle negative-dividied-by-negative cases
	{
		denominator *= -1;
		numerator *= -1;
	}

	if(reduceInput) reduce();
}

void fraction::reduce()
{
	//Idea - [implimented as Method 2] iterate over every value up to the size of the numerator/denominator from 2 -> numer/denom because the smaller values will be factored out first meaning that 2, 3 will be factored out instead of 6
	//Idea - [implimented by re-introcing Method 1 and tweaking Method 2] Run method 1 first to reduce the fraction efficiently (using method 1, only using predetermined prime numbers),
			//and then if the numerator and denominator of the resulting fraction are both greater than the last predetermined prime number, apply 
			//method 2 starting at factor = the last prime + 1

	bool isNegative = (numerator < 0 ? true : false);	//If the numerator is less than 0 it is negative, so the flag is set to true.  The flag is used to store the negative separatley
					//from the fraction, so the factoring code can work properly.  The negative will be re-introduced later (if applicable) just before the function exits

	if(isNegative) numerator *= -1;	//If the numerator is less than 0, flip it to positive for use inside this function

	std::vector<int> primeFactors {2, 3, 5, 7, 11, 13};	//A vector containing pretermined prime factors, used to efficiently reduce fractions by skipping non-prime numbers


	//Method 1 - reduces the fraction using a list of known primes
	{
		for(auto iter = primeFactors.begin(); iter != primeFactors.end(); iter++)
		{
			int factor = *iter;

			if(numerator >= factor && denominator >= factor)	//If the value we're trying to factor out is bigger than the numerator and/or denominator, it just won't work
			{

				while(numerator%factor == 0 && denominator%factor == 0)	//If we divide the top and bottom by 'factor' and the remainder for both is 0, we can factor 'factor' out of the fraction
				{

					//This is handled as individual elements instead of doing it as a fraction / int because we would end up in an infinite loop otherwise
					numerator /= factor;
					denominator /= factor;
				}
			}
			else
			{
				if(isNegative) numerator *= -1;
				return;	//If we exit here because the numerator and/or denominator is less than the value we're trying to factor, we know that the value is within the list of known primes,
							//and therefore can't be reduced further in Method 2, and can be skipped
			}
		}
	}

	//Method 2 - if the numerator and denominator of the resulting fraction are still greater than the final known prime, start immediatly after the last known prime and check to see
	{		//if it can be used to reduce the fraction, looping to check for every value up until the numerator or denominator (whichever's lower)

		for(int factor = primeFactors[primeFactors.size() - 1] + 1; factor <= numerator && factor <= denominator; factor++)
		{
			while(numerator%factor == 0 && denominator%factor == 0)	//If we divide the top and bottom by 'factor' and the remainder for both is 0, we can factor 'factor' out of the fraction
			{

				//This is handled as individual elements instead of doing it as a fraction / int because we would end up in an infinite loop otherwise
				numerator /= factor;
				denominator /= factor;
			}
		}
	}
	if(isNegative) numerator *= -1;


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