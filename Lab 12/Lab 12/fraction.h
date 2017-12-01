// Header file fraction.h declares class fraction.
class fraction
// Class fraction represents the numerator and
// denominator of a fraction.
{
public:
	fraction() {}
	fraction(int Numerator, int Denominator, bool reduceInput = true);

private:
	int numerator;
	int denominator;

public:
	int getNumerator() { return numerator; }
	int getDenominator() { return denominator; }

	void reduce();	//Simplify the fraction as much as possible
	fraction getInverse();

	//Converts first and second to fractions with the same base
	std::pair<fraction, fraction> convertToCommonDenominator(fraction first, fraction second);

	fraction operator+(fraction other);
	fraction operator-(fraction other);
	fraction operator*(fraction other);
	fraction operator*(int other);
	fraction operator/(fraction other);
	fraction operator/(int other);

};


