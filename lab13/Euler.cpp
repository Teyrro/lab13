#include "DE.h"
#include <iomanip>

void Euler::PrintY(std::vector<double> y) {
	std::cout << "Y = ( ";
	for (auto& ptr : y) {
		std::cout << std::fixed << ptr << " ";
	}
	std::cout << ") ";
}
void Euler::PrintList(std::list<std::vector<double>> const& list) {
	for (auto it(list.begin()); it != list.end(); it++) {
		PrintY((*it));
	}
}

void Euler::VectorSum(std::vector<double>& x, std::vector<double> const& y) {
	for (int i(0); i < y.size(); i++) {
		x[i] += y[i];
	}
}
void Euler::VectorMul(std::vector<double>& y, double x) {
	for (int i(0); i < y.size(); i++) {
		y[i] *= x;
	}
}

void Euler::MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
	std::vector<double> yTemp, newY(y);
	double newX = x;
	int size = ((xEnd - x) + h * 0.1) / h;
	for (int i(0); i < size; i++) {
		yTemp = TemplateFunc(newX, newY, h);

		//std::cout << "x = " << x << "\n";
		//PrintY(y);
		//std::cout << " + ";
		//PrintY(Func(x, y, 1));
		//std::cout << " * " << h << " = ";
		//PrintY(yTemp);
		//std::cout << "\n\n";

		newX += h;
		newY = yTemp;
		list.push_back(newY);
	}
}

void Euler::DeleteUnusefullValue(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp) {
	std::list<std::vector<double>> newList, TempList(listTemp);

	//PrintList(listTemp);
	//std::cout << "\n";
	auto it(list.begin()), it2(TempList.begin()) ;
	int difference(listTemp.size() / list.size() - 1);
	while (!listTemp.empty()) {
		for (int i(0); i < difference; i++) {
			listTemp.pop_front();
		}
		
		VectorSum(*it2, *it);
		VectorMul(*it2, 1 / 3);
		VectorSum(*it2, listTemp.front());

		newList.push_back(listTemp.front());
		listTemp.pop_front();


		it++, it2++;
		//PrintList(newList);
		//std::cout << "\n";
		//PrintList(listTemp);
		//std::cout << "\n";
	}
	listTemp = newList;
	//PrintList(listTemp);
}

bool Euler::Compare(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp) {
	DeleteUnusefullValue(list, listTemp);

	PrintList(list);
	std::cout << "\n";
	PrintList(listTemp);
	std::cout << "\n";

	auto it(list.begin()), it2(listTemp.begin());
	double delta(0);

	for (it, it2; it != list.end(); it++, it2++) {

		for (int i(0); i < y.size(); i++) {

			if (abs((*it)[i] - (*it2)[i]) > delta) {
				delta = abs((*it)[i] - (*it2)[i]);
				//PrintY((*it)), PrintY((*it2));
				//std::cout << "\ny_" << i << "(" << (*it)[i] << ") - " << "y2_" << i << "(" << (*it2)[i] << ") " << abs((*it)[i] - (*it2)[i]) << " < " << 3 * eps << "\n";
			}
			//std::cout << "y_" << i << "(" << (*it)[i] << ") - " << "y2_" << i << "(" << (*it2)[i] << ") " << abs((*it)[i] - (*it2)[i]) << " < " << 3 * eps << "\n";
		}

	}
	if (delta < realEps) {
		std::cout << "delta: " << delta << " < eps: (" << realEps << ")" "\n";
		return false;
	}

	list = listTemp;
	std::cout << "Required precision not found" << " delta: " << delta << " < eps: (" <<  realEps << ")" << "\n\n";
	listTemp.clear();
	return true;
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
