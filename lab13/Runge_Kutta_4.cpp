#include "Runge_Kutta_4.h"

std::vector<double> Runge_Kutta_4::TemplateFunc(double x, std::vector<double> y, double h) {
	std::vector<double> equation(y);
	std::vector<double> K(y.size());
	double sum(0);
	int q(1), p(1);
	for (int i(0); i < 4; i++) {
		VectorMul(K, sum);
		VectorSum(K, y);

		K = (Func(x + sum, K, 1));

		//std::cout << "Y0_" << i << ": ";
		//PrintY(equation);
		//std::cout << "\n";

		//std::cout << "K_" << i << ": ";
		//PrintY(K);
		//std::cout << "\n";

		for (int i(0); i < equation.size(); i++) {

			equation[i] += p * K[i] * (h / 6);
		}

		if (i % 2 == 0) {
			sum += h / 2;
			p += q;
			q = -q;
		}
	}
	//PrintY(equation);
	//std::cout << "\n";
	return equation;
}

void Runge_Kutta_4::MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
	std::vector<double> yTemp(y);
	double newX = x;
	int size = ((xEnd - x) + h * 0.1) / h;
	for (int i(0); i < size; i++) {
		yTemp = TemplateFunc(newX, yTemp, h);

		newX += h;
		list.push_back(yTemp);
	}

}