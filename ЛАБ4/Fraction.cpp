#include "Fraction.h"

using namespace std;
using namespace Math;

Fraction::Fraction() : Fraction(0, 0, 1)
{
}
Fraction::Fraction(int _num) : Fraction(0, _num, 1)
{
}
Fraction::Fraction(int _num, int _denom) : Fraction(0, _num, _denom)
{
}

Fraction::Fraction(int intPart, int _num, int _denom) : num(_num), denom(_denom)
{
	if (intPart && (_num < 0 || _denom < 0))
		throw string("Только целая часть может быть отрицательной!");
	if (denom == 0)
		throw string("Знаменатель не должен быть равен 0!");
	if (intPart)
	{
		if (intPart < 0)
		{
			num = intPart * denom - num;
		}
		else
		{
			num += intPart * denom;
		}
	}
	Reduction();
}

//Fraction::Fraction(const Fraction & frac1) : Fraction(frac1.num, frac1.denom)
//{
//}
//
//Fraction::Fraction(Fraction && frac1) noexcept : Fraction()
//{
//	operator=(frac1);
//}
//
//Fraction::~Fraction() {}


void Fraction::Reduction()
{
	if (denom == 0)
		throw string("Знаменатель не может быть равен 0!");
	if (denom < 0)
	{
		denom = -denom;
		num = -num;
	}
	if (num == 0)
		denom = 1;
	else
	{
		int tempDenom = denom,
			tempNum = num;
		if (tempNum < 0)
			tempNum = -tempNum;

		int	ost = tempDenom % tempNum;
		while (ost != 0)
		{
			tempDenom = tempNum;
			tempNum = ost;
			ost = tempDenom % tempNum;
		}
		int nod = tempNum;
		if (nod != 1)
		{
			num /= nod;
			denom /= nod;
		}
	}
}

int Fraction::GetIntPart() const
{
	return num / denom;
}
Fraction Fraction::GetRem() const
{
	return Fraction(num % denom, denom);
}

int Fraction::NOK(int num1, int num2) const
{
	return num1 * num2 / NOD(num1, num2);
}


int Fraction::NOD(int num1, int num2) const
{
	int n1 = num1;
	int n2 = num2;
	while (n1 != n2)
	{
		if (n1 > n2)
			n1 -= n2;
		else
			n2 -= n1;
	}
	return n1;
}
int Fraction::GetNum() const
{
	return num;
}

int Fraction::GetDenom() const
{
	return denom;
}

void Fraction::SetNum(int value)
{
	num = value;
	Reduction();
}

void Fraction::SetDenom(int value)
{
	denom = value;
	Reduction();
}

//Fraction & Fraction::operator=(const Fraction & frac1)
//{
//	if (this != &frac1)
//	{
//		num = frac1.num;
//		denom = frac1.denom;
//	}
//	return *this;
//}
//
//Fraction Fraction::operator=(Fraction && frac1)	noexcept
//{
//	if (this != &frac1)
//	{
//		swap(num, frac1.num);
//		swap(denom, frac1.denom);
//	}
//	return *this;
//}

Fraction& Fraction::operator+=(const Fraction& frac1)
{
	int tempDenom = NOK(denom, frac1.denom);
	num = ((tempDenom / denom) * num);
	denom = tempDenom;
	num += ((frac1.num) * (tempDenom / frac1.denom));

	Reduction();
	return *this;
}
Fraction& Fraction::operator-=(const Fraction& frac1)
{
	int tempDenom = NOK(denom, frac1.denom);
	num = ((tempDenom / denom) * num);
	denom = tempDenom;
	num -= ((frac1.num) * (tempDenom / frac1.denom));

	Reduction();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& frac1)
{
	int tempNum = NOD(num, frac1.denom);
	int tempDen = NOD(denom, frac1.num);
	num /= tempNum;
	denom /= tempDen;
	num *= (frac1.num/tempDen);
	denom *= (frac1.denom/tempNum);

	Reduction();
	return *this;
}
Fraction& Fraction::operator/=(const Fraction& frac1)
{
	int tempNum = NOD(num, frac1.num);
	int tempDen = NOD(denom, frac1.denom);
	num /=tempNum;
	denom /= tempDen;
	num *= (frac1.denom / tempDen);
	denom *= (frac1.num / tempNum);

	Reduction();
	return *this;
}

Fraction Math::operator+(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) += frac2;
}

Fraction Math::operator-(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) -= frac2;
}

Fraction Math::operator*(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) *= frac2;
}

Fraction Math::operator/(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) /= frac2;
}

ostream& Math::operator<<(ostream& output, const Fraction& frac1)
{
	if ((frac1.denom != 1) && (frac1.num != 0))
		output << " " << frac1.num << "/" << frac1.denom;
	else
		output << frac1.num;
	return output;

}