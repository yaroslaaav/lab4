#pragma once
#include <iostream>

namespace Math
{
	class Fraction
	{
	private:
		int num;
		int denom;

	public:
		Fraction();
		Fraction(int);
		Fraction(int, int);
		Fraction(int, int, int);
		//Fraction(const Fraction &frac1);//
		//Fraction(Fraction&&frac1) noexcept;//
		//~Fraction();//

		void Reduction();

		int GetIntPart() const;
		Fraction GetRem() const;

		int NOK(int ,int) const;
		int NOD(int, int) const;

		int GetNum() const;
		int GetDenom() const;

		void SetNum(int);
		void SetDenom(int);

		//Fraction &operator = (const Fraction &frac1);//
		//Fraction operator=(Fraction && frac1) noexcept;//

		Fraction& operator+=(const Fraction& frac1);
		Fraction& operator-=(const Fraction& frac1);
		Fraction& operator*=(const Fraction& frac1);
		Fraction& operator/=(const Fraction& frac1);

		friend Fraction operator + (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator - (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator * (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator / (const Fraction& frac1, const Fraction& frac2);

		friend std::ostream& operator<<(std::ostream& output, const Fraction& frac1);
	};
}
