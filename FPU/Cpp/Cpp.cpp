#include "stdafx.h"
#include <iostream>

double F(double x, int n)
{
	double res = 0;
	if (n < 1) return 0;
	_asm
	{
		finit
		mov ecx, n
		fld1  // st5 i increment step = 1
		fld x // st4 x
		fldz  // st3 sum
		fldz  // st2 curr i
		fld1  // st1 curr i!
		fldz  // st0 curr (i*x)

	cyc:fld st(0)		    // load curr (i*x)
		fcos			    // calc cos(i*x) 
		fdiv st(0), st(2)   // calc cos(i*x)/i! 
		faddp st(4), st(0)  // sum += cos(i*x)/i!
		//------------------------
		fld st(2)			// curr i += 1
		fadd st(0), st(6)
		fstp st(3)
		//------------------------
		fadd st(0), st(4)	// curr (i*x) += x
		//------------------------
		fld st(1)			// curr (i!) *= i
		fmul st(0), st(3)
		fstp st(2)
		loop cyc

		fld st(3)
		fst res
	}
	return res;
}
double F(double x, double eps)
{
	double res;
	_asm
	{
		finit

				// st7 for use
		fld eps // st6 epsilon
		fldz    // st5 previous series element
		fld x   // st4 x
		fldz    // st3 sum
		fldz    // st2 curr i
		fld1    // st1 curr (i!)
		fldz    // st0 curr (i*x)

		//-----------------  Calculate next element of series and add it to sum
   cyc: fld st(0)		    // load curr (i*x)
		fcos			    // calc cos(i*x) 
		fdiv st(0), st(2)   // calc cos(i*x)/i! 
		fadd st(4), st(0)   // sum += cos(i*x)/i!
		//------------------ Compare difference between current and previous elements of series and Epsilon
		fabs				// curr = abs(cur)
		fxch st(6)			// curr <-> pred
		fsub st(0), st(6)	// pred = pred - curr
		fabs				// calc |pred - curr|
		fcom st(7)			// compare |pred - curr| and Epsilon
		fstsw ax
		sahf
		jbe ext				// if (|pred - curr| <= eps ) goto: ext
		fstp st(0)			
		//------------------ calculating next i, i*x, i! by recurrence
		//------------------ curr i += 1
		fld1				
		fadd st(3), st(0)
		fstp st(0)
		//------------------ curr (i*x) += x
		fadd st(0), st(4)	
		//------------------ curr (i!) *= i
		fld st(1)			
		fmul st(0), st(3)
		fstp st(2)
		jmp cyc

   ext: fxch st(4)
		fstp res
	}
	return res;
}
double Fcheck(double x)
{
	return cos(sin(x))*exp(cos(x));
}
int main()
{
	int n; 
	double eps,x;
	std::cout << "Task: Taylor series by FPU. Var 30. F(x) = cos(sin(x))*E^(cos(x))." << '\n';
	std::cout << "Enter n: ";
	std::cin >> n;
	std::cout << "Enter x: ";
	std::cin >> x;
	std::cout << "Enter epsilon: ";
	std::cin >> eps;

	std::cout << "Sum until > epsilon: " << F(x, eps) <<'\n';
	std::cout << "Sum of first n: " << F(x, n) <<'\n';
	std::cout << "By C build-in functions: " << Fcheck(x) << '\n';
	return 0;
}

