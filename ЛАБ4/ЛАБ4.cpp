#include <iostream>
#include <string>
#include "math.h"

#include "Fraction.h"
#include "Polynomial.h"


using namespace std;
using namespace Math;

int main()
{
	setlocale(LC_ALL, "rus");
	try
	{
		Fraction a(1, 1000000);
		Fraction b(999999, 1000000);
		cout << a/b << endl;
		//double arr1[] = { -2,10,12,-5,1,2};
		//double arr2[] = { 7,-2, 0, 1};
		//Polynomial a(5, arr1);
		//Polynomial b(3, arr2);
		//cout << a[3] << endl;
	}
	catch (const string & std)
	{
		cout << std << endl;
	}
}

