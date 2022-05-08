#include "DE.h"
#include "SimpModEulerT.h"
#include "SimpModEulerD.h"
#include "Runge_Kutta_4.h"
#include "NE.h"
#include <iostream>

void FindInterv(double& left, double& right, double x, double nextValueY, std::function<double(double)> F) {
	short i(1);
	double need(F(x)), newX(x);
	if (need < nextValueY) {
		left = x;
		while (need < nextValueY) {
			newX += i;
			need = F(newX);
		}
		right = newX;
	}
	else {
		right = x;
		i *= -1;
		while (need > nextValueY) {
			newX += i;
			need = F(newX);
		}
		left = newX;
	}
}

double FuncForMyNewMark(double y) {
	return sin(y) + y;
}

double MoreFunc(double x, std::vector<double> equation, double step) {
	double y((exp(x) + equation[0] + equation[1]) / 3);
	
	//std::cout << x  << " + " << equation[0] << " * " << pow(x, 2) << " - " << equation[1] << " * " << step << "\n";
	//double y((x + equation[0] * pow(x, 2) - equation[1]));
	//double y(x * equation[1] + equation[0]);
	//double y(sin(equation[0]) + exp(x));


	//double left, right;
	//FindInterv(left, right, x, y, FuncForMyNewMark);
	//NE a(left, right, FuncForMyNewMark, y);
	//y = a.MPD1(pow(10, -4), true);

	return y * step;
}

//double Func(double x) {
//	return x * 2 - 4;
//}

int main() {
	int precision(4);
	double left(0), right(3), step(1);
	std::vector<double> SDE{ 2, NULL };

	//Euler a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	SimpModEulerT a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	//SimpModEulerD a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	//Runge_Kutta_4 a(left, right, step, SDE, pow(10, -precision), MoreFunc, precision);
	a.NEForFindingK(1, 2.718);
	a.FindAnswer();

	//NE a(1, 4, Func, 0);
	//a.MPD(pow(10, -4), true);
}