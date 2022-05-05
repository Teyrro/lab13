#include <iostream>
#include "DE.h"

double MoreFunc(double x, std::vector<double> equation, double step) {
	return (x * equation[1] + equation[0]) * step;
}


int main() {
	int precision(7);
	double left(1), right(1.6), step(0.2);
	std::vector<double> SDE{ 2, -1 };

	//Euler a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	//SimpModEulerT a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	//SimpModEulerD a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	//Runge_Kutta_4 a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	//a.FindAnswer();
}