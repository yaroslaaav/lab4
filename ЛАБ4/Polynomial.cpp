#include "Polynomial.h"

using namespace std;
using namespace Math;

Polynomial::Polynomial() : Polynomial(0, NULL)
{
}
Polynomial::Polynomial(int new_deg) : Polynomial(new_deg, NULL)
{
}

Polynomial::Polynomial(int new_deg, const double* new_koef) {

	if (new_deg < 0)
		throw string("Степень полинома не может быть меньше 0!");
	deg = new_deg;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; ++i)
	{
		if (new_koef != 0)
			koef[i] = new_koef[i];
		else
			koef[i] = 0;
	}
}

Polynomial::Polynomial(const Polynomial& pol1) :Polynomial::Polynomial(pol1.deg, pol1.koef)
{
}

Polynomial::Polynomial(Polynomial&& pol1) noexcept : Polynomial::Polynomial()
{
	operator=(pol1);
}

Polynomial::~Polynomial() {
	if (koef != 0)
	{
		delete[] koef;
		koef = NULL;
	}
}

int Polynomial::GetDeg() const
{
	return deg;
}

Polynomial& Polynomial::operator = (const Polynomial& pol1)
{
	if (this != &pol1)
	{
		if (deg != pol1.deg)
		{
			if (koef)
			{
				delete[] koef;
				koef = nullptr;
			}
			koef = new double[pol1.deg + 1];
			deg = pol1.deg;
		}
		for (int i = 0; i <= deg; i++)
		{
			koef[i] = pol1.koef[i];
		}
	}
	return *this;
}

Polynomial& Polynomial::operator=(Polynomial&& pol1) noexcept
{
	if (this != &pol1)
	{
		swap(koef, pol1.koef);
		swap(deg, pol1.deg);
	}
	return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& pol1)
{
	if (deg >= pol1.deg)
	{
		for (int i = pol1.deg; i >= 0; i--)
			koef[i] += pol1.koef[i];
	}
	if (deg < pol1.deg)
	{
		Polynomial fortime(pol1);
		fortime += *this;
		*this = move(fortime);
	}
	CorrectDeg();
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& pol1)
{
	if (deg >= pol1.deg)
	{
		for (int i = pol1.deg; i >= 0; i--)
			koef[i] -= pol1.koef[i];
	}

	if (deg < pol1.deg)
	{
		Polynomial fortime(pol1.deg);
		for (int i = pol1.deg; i > deg; i--)
			fortime.koef[i] = -pol1.koef[i];
		for (int i = deg; i >= 0; i--)
			fortime.koef[i] = koef[i] - pol1.koef[i];
		*this = move(fortime);
	}
	CorrectDeg();
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& pol1)
{
	int max = deg + pol1.deg;
	Polynomial fortime(max);
	for (int i = deg; i >= 0; i--)
	{
		for (int j = pol1.deg; j >= 0; j--)
			fortime.koef[i + j] += koef[i] * pol1.koef[j];
	}
	*this = move(fortime);
	CorrectDeg();
	return *this;
}

Polynomial& Polynomial::operator*=(double k)
{
	for (int i = deg; i >= 0; i--)
		koef[i] *= k;
	CorrectDeg();
	return *this;
}

Polynomial& Polynomial::operator/=(const Polynomial& pol1)
{
	if (pol1.koef[pol1.deg] == 0)
		throw string("Деление на 0!");
	if (deg < pol1.deg)
		return *this = Polynomial(0);
	Polynomial result(deg - pol1.deg);
	for (int i = 0; i <= result.deg; i++)
	{
		result.koef[result.deg - i] = koef[deg - i] / pol1.koef[pol1.deg];
		for (int j = 0; j <= pol1.deg; j++)
		{
			koef[deg - j - i] -= pol1.koef[pol1.deg - j] * result.koef[result.deg - i];
		}
	}
	result.CorrectDeg();
	return *this = move(result);
}

Polynomial& Polynomial::operator%=(const Polynomial& pol1)
{
	if (pol1.koef[pol1.deg] == 0)
		throw string("Деление на 0!");
	if (deg < pol1.deg)
		return *this;
	double k;
	for (int i = 0; i <= deg - pol1.deg; i++)
	{
		k = koef[deg - i] / pol1.koef[pol1.deg];
		for (int j = 0; j <= pol1.deg; j++)
		{
			koef[deg - j - i] -= pol1.koef[pol1.deg - j] * k;
		}
	}
	CorrectDeg();
	return *this;
}

Polynomial Math::operator + (const Polynomial& pol1, const Polynomial& pol2) {

	return Polynomial(pol1) += pol2;
}

Polynomial Math::operator-(const Polynomial& pol1, const Polynomial& pol2)
{
	return Polynomial(pol1) -= pol2;
}

Polynomial Math::operator*(const Polynomial& pol1, const Polynomial& pol2)
{
	return Polynomial(pol1) *= pol2;
}

Polynomial Math::operator * (const Polynomial& pol1, double k) {
	return Polynomial(pol1) *= k;
}


Polynomial Math::operator * (double k, const Polynomial& pol1) {

	return operator*(pol1, k);
}

Polynomial Math::operator/(const Polynomial& pol1, const Polynomial& pol2)
{
	return Polynomial(pol1) /= pol2;
}
Polynomial Math::operator%(const Polynomial& pol1, const Polynomial& pol2)
{
	return Polynomial(pol1) %= pol2;
}

double Polynomial::operator()(double k) const
{
	double res = 0;
	for (int i = deg; i >= 0; i--)
		res = koef[i] + (res * k);
	return res;
}

double& Polynomial::operator[](int index)
{
	if (index < 0 || index > deg)
		throw string("Степень не существует!");
	return koef[index];
}

double Polynomial::operator[](int index) const
{
	if (index < 0 || index > deg)
		throw string("Степень не существует!");
	return koef[index];
}

void Polynomial::CorrectDeg() {
	if (deg > 0)
	{
		int x = deg;
		if (koef[x] == 0)
		{
			do
			{
				x--;
			} while (x && koef[x] == 0);
		}
		if (x != deg)
		{
			Polynomial fortime(x, koef);
			*this = move(fortime);
		}
	}

}

ostream& Math::operator<<(ostream& output, const Polynomial& pol1)
{
	int i;
	for (i = pol1.deg; i >= 0; i--)
	{
		if (pol1.koef[i] != 0)
		{
			if (pol1.koef[i] > 0)
				output << "+" << pol1.koef[i];
			if (pol1.koef[i] < 0)
				output << "-" << -1 * pol1.koef[i];
			if (i > 0)
				output << "X^" << i;
			output << " ";
		}
	}
	return output;
}
