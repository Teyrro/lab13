#include "DE.h"
void Euler::PrintY(std::vector<double> y) {
	std::cout << "Y = ( ";
	for (auto& ptr : y) {
		std::cout << ptr << " ";
	}
	std::cout << ") ";
}

void Euler::PrintList(std::list<std::vector<double>> const& list) {
	for (auto it(list.begin()); it != list.end(); it++) {
		PrintY((*it));
	}
}

std::vector<double> Euler::TemplateFunc(double x, std::vector<double> y, double h) {
	std::vector<double> equation(y);
	std::vector<double> tmpEquation(Func(x, equation, h));
	for (int i(0); i < equation.size(); i++) {
		equation[i] += tmpEquation[i];
	}
	return equation;
}

std::vector<double> Euler::Func(double x, std::vector<double> equation, double step) {
	std::vector<double> NewEquation(equation.size());
	for (int i(0); i < equation.size() - 1; i++) {
		NewEquation[i] = equation[i + 1] * step;
	}
	NewEquation[equation.size() - 1] = MoreFunc(x, equation, step);
	return NewEquation;
}
