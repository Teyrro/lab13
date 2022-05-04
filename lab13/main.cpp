#include <iostream>
#include "DE.h"

double MoreFunc(double x, std::vector<double> equation, double step) {
	return (x * equation[1] + equation[0])* step;
}


int main() {
	Runge_Kutta_4 a(1, 1.4, 0.2, {2, -1}, pow(10, -3), MoreFunc);
	a.FindAnswer();
}