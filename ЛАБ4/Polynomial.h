#pragma once
#include <iostream>;

namespace Math
{
	class Polynomial
	{
	private:
		int deg;
		double* koef;
		void CorrectDeg();
	public:
		Polynomial();
		explicit Polynomial(int);
		Polynomial(int, const double*);
		Polynomial(const Polynomial& pol1);
		Polynomial(Polynomial&& pol1) noexcept;
		~Polynomial();

		int GetDeg() const;
		Polynomial& operator = (const Polynomial& pol1);
		Polynomial& operator = (Polynomial&& pol1) noexcept;

		Polynomial& operator += (const Polynomial& pol1);
		Polynomial& operator -= (const Polynomial& pol1);

		Polynomial& operator *=(const Polynomial& pol1);
		Polynomial& operator *=(double k);

		Polynomial& operator %=(const Polynomial& pol1);
		Polynomial& operator /=(const Polynomial& pol1);

		friend Polynomial operator + (const Polynomial& pol1, const Polynomial& pol2);
		friend Polynomial operator - (const Polynomial& pol1, const Polynomial& pol2);

		friend Polynomial operator * (const Polynomial& pol1, const Polynomial& pol2);
		friend Polynomial operator * (const Polynomial& pol1, double k);
		friend Polynomial operator * (double k, const Polynomial& pol1);

		friend Polynomial operator / (const Polynomial& pol1, const Polynomial& pol2);
		friend Polynomial operator % (const Polynomial& pol1, const Polynomial& pol2);

		double operator()(double k) const;

		double& operator[] (int index);
		double operator[](int index) const;

		friend std::ostream& operator<<(std::ostream& output, const Polynomial& pol1);
	};

}