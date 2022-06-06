#include "DE.h"
#include "NE.h"

#include <iomanip>

void Euler::PrintY(std::vector<double> y) {
	
	std::cout << "Y = ( ";
	for (auto& ptr : y) {
		std::cout << std::fixed << ptr << " ";
	}

	std::cout << ") ";
}

void Euler::PrintY(std::vector<double> y, double x) {

	std::cout << "Y = ( ";
	for (auto& ptr : y) {
		std::cout << std::fixed << ptr << " ";
	}
	std::cout << y[0] / exp(x) << " ";
	std::cout << exp(x) << " ";
	std::cout << ") ";
}

void Euler::PrintList(std::list<std::vector<double>> const& list) {
	//std::cout << "ListY: \n";
	
	for (auto it(list.begin()); it != list.end(); it++) {
		PrintY((*it));
		std::cout << "\n";
	}
}
void Euler::PrintList(std::list<std::vector<double>> const& list, double h) {
	//std::cout << "ListY: \n";
	double newX(x + h);
	std::cout << "\tx\t\t   y\t\ty'\t   y/e^x\t e^x\n";
	std::cout << "X " << x << "\t";
	PrintY(y, x);
	std::cout << "\n";

	for (auto it(list.begin()); it != list.end(); it++) {
		std::cout << "X " << newX << "\t";
		PrintY((*it), newX);
		std::cout << "\n";
		newX += h;
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
	std::vector<double> yTemp(y);
	double newX(x);
	int size = ((xEnd - x) + h * 0.1) / h;
	for (int i(0); i < size; i++) {
		yTemp = TemplateFunc(newX, yTemp, h);

		//std::cout << "x = " << x << "\n";
		//PrintY(y);
		//std::cout << " + ";
		//PrintY(Func(x, y, 1));
		//std::cout << " * " << h << " = ";
		//PrintY(yTemp);
		//std::cout << "\n\n";

		newX += h;
		list.push_back(yTemp);
	}
}

void Euler::DeleteUnusefullValue(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp) {
	std::list<std::vector<double>> newList, TempList(listTemp);

	//PrintList(listTemp);
	//std::cout << "\n";
	auto it(list.begin());
	int difference(listTemp.size() / list.size() - 1);
	while (!listTemp.empty()) {
		for (int i(0); i < difference; i++) {
			listTemp.pop_front();
		}
		//auto it2(TempList.begin());
		//VectorSum(*it2, *it);
		//VectorMul(*it2, 1 / 3);
		//VectorSum(*it2, listTemp.front());

		newList.push_back(listTemp.front());
		listTemp.pop_front();


		//it++;	
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

	std::cout << "h = " << h*2 << "\n";
	PrintList(list, tmpH);
	std::cout << "\n";
	std::cout << "h = " << h << "\n";
	PrintList(listTemp, tmpH);
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

	list = listTemp;
	if (delta < realEps) {
		std::cout << "delta: " << delta << " < eps: (" << realEps << ")" "\n";
		return false;
	}

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

void Euler::FindAnswer() {

	std::list<std::vector<double>> listTemp(list);
	double factor(1);
	std::cout << h << "\n";
	MethodFA(y, h, list);
	do {
		h /= 2;
		MethodFA(y, h, listTemp);
		//PrintList(listTemp);

		std::cout << "Size list " << list.size() << ", Size listH/2 " << listTemp.size() << "\n";
		//PrintY(y);
	} while (Compare(list, listTemp));
}

double Euler::F(double x) {
	y[index] = x;
	MethodFA(y, h, list);

	//PrintList(list);
	//std::cout << '\n';

	auto it(list.begin());
	std::advance(it, stepCount);

	//PrintY(*it);
	//std::cout << "\n\n";

	double answer = (*it)[index - 1];
	list.clear();

	return answer;
}

//Y'' = func(x,y)
//Y(0) = 1
//Y'(0) = 0

//Y'' = func(x,y)
//Y(0) = 1
//Y(1) = 2.718

void Euler::NEForFindingK(double nextValueX, double nextValueY) {
	stepCount = ((abs(nextValueX - x) + h * 0.1) / h) - 1;
	float i(tmpH);
	double left, right, need(F(x)), newX(nextValueX);
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
		while (need > nextValueY) {
			newX -= i;
			need = F(newX);
		}
		left = newX;
	}


	using std::placeholders::_1;
	NE findCoord(left, right, std::bind(&Euler::F, this, _1), nextValueY, prec);
	//NE findCoord(nextValueY1, nextValueY2, *this);
	findCoord.MPD(eps, false);
	
	MethodFA(y, tmpH, list);
	PrintList(list, tmpH);
	std::cout << "\n";
	//else {
	//	std::cout << "Input Other Interval, current value: " << a << " * " << b << "\n";
	//}

}
