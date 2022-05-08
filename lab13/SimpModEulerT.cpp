#include "SimpModEulerT.h"

void SimpModEulerT::MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
	std::vector<double> yTemp, yi, newY(y);
	double newX(x);
	int size = ((xEnd - x) + h * 0.1) / h;
	for (int i(0); i < size; i++) {
		yi = TemplateFunc(newX, newY, newY, h / 2);
		yTemp = TemplateFunc(newX + h / 2, newY, yi, h);

		//std::cout << "x = " << newX << "\n";
		//PrintY(newY);
		//std::cout << " + ";
		//PrintY(TemplateFunc(newX, newY, newY, h / 2));
		//std::cout << " * " << h / 2 << " = ";
		//PrintY(yTemp);
		//std::cout << "\n\n";

		newX += h;
		newY = yTemp;
		list.push_back(newY);
	}
}

std::vector<double> SimpModEulerT::TemplateFunc(double x, std::vector<double> y, std::vector<double> newY, double h) {
	std::vector<double> tmpEquation(Func(x, newY, h));
	for (int i(0); i < y.size(); i++) {
		y[i] += tmpEquation[i];
	}
	return y;
}