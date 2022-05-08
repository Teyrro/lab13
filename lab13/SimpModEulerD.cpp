#include "SimpModEulerD.h"



void SimpModEulerD::MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
	std::vector<double> yTemp, yi, newY(y);
	double newX = x;
	int size = ((xEnd - x) + h * 0.1) / h;
	for (int i(0); i < size; i++) {
		yi = TemplateFunc(newX, newY, newY, h / 2);
		yTemp = TemplateFunc(newX + h, newY, yi, h / 2);
		Add(yTemp, Func(newX, newY, h / 2));

		//std::cout << "x = " << newX << "\n";
		//PrintY(newY);
		//std::cout << " + ";
		//PrintY(Func(newX, newY, h/2));
		//PrintY(yTemp);
		//std::cout << "\n\n";

		newX += h;
		newY = yTemp;
		list.push_back(newY);
	}
}

std::vector<double> SimpModEulerD::TemplateFunc(double x, std::vector<double> y, std::vector<double> newY, double h) {
	std::vector<double> tmpEquation(Func(x, newY, h));
	for (int i(0); i < y.size(); i++) {
		y[i] += tmpEquation[i];
	}
	return y;
}

void SimpModEulerD::Add(std::vector<double>& y, std::vector<double> y2) {
	for (int i(0); i < y.size(); i++) {
		y[i] += y2[i];
	}
}