#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <functional>

class Euler {
protected:
	double x, xEnd, h, eps;
	std::vector<double> y;
	std::list<std::vector<double>> list;
	std::function<double(double, std::vector<double>, double)> MoreFunc;

	std::vector<double> Func(double x, std::vector<double> equation, double step);
	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, double h);
	void PrintList(std::list<std::vector<double>> const& list);
	void PrintY(std::vector<double> y);
	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
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
	void DeleteUnusefullValue(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp) {
		std::list<std::vector<double>> newList;
		//PrintList(listTemp);
		//std::cout << "\n";
		int difference(listTemp.size() / list.size() - 1);
		while (!listTemp.empty()) {
			newList.push_back(listTemp.front());

			for (int i(0); i < difference + 1; i++) {
				listTemp.pop_front();
			}

			//PrintList(newList);
			//std::cout << "\n";
			//PrintList(listTemp);
			//std::cout << "\n";
		}
		listTemp = newList;
		//PrintList(listTemp);
	}
	bool Compare(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp) {
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
		if (delta < 3 * eps) {
			std::cout << "delta: " << delta << " < 3 * eps: (" << 3 * eps << ")" "\n";
			return false;
		}

		list = listTemp;
		std::cout << "Required precision not found" << " delta: " << delta << " > 3 * eps: (" << 3 * eps << ")" << "\n\n";
		listTemp.clear();
		return true;
	}
public:
	Euler(double X0, double Xn, double h, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func) 
	: x(X0), xEnd(Xn), y(Y), h(h), eps(e), MoreFunc(func)
	{

	}

	virtual void FindAnswer() {	
		
		std::list<std::vector<double>> listTemp(list);
		double factor(1);
		MethodFA(y, h, list);
		do {
			h /= 2;
			std::cout << "h = " << h << "\n";
			MethodFA(y, h, listTemp);
		
			std::cout << "Size list " << list.size() << ", Size listH/2 " << listTemp.size() << "\n";
			//PrintY(y);
		} while (Compare(list, listTemp));
	}
};


class SimpModEulerT : public Euler {
protected:
	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
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
	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, std::vector<double> newY, double h) {
		std::vector<double> tmpEquation(Func(x, newY, h));
		for (int i(0); i < y.size(); i++) {
			y[i] += tmpEquation[i];
		}
		return y;
	}
public:
	SimpModEulerT(double X0, double Xn, double n, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func)
	: Euler(X0, Xn, n, Y, e, func) 
	{

	}

};

class SimpModEulerD : public Euler {
	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
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

	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, std::vector<double> newY, double h) {
		std::vector<double> tmpEquation(Func(x, newY, h));
		for (int i(0); i < y.size(); i++) {
			y[i] += tmpEquation[i];
		}
		return y;
	}
	void Add(std::vector<double>& y, std::vector<double> y2) {
		for (int i(0); i < y.size(); i++) {
			y[i] += y2[i];
		}
	}
public:
	SimpModEulerD(double X0, double Xn, double n, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func)
	: Euler(X0, Xn, n, Y, e, func) 
	{

	}
};

class Runge_Kutta_4 : public Euler {
	void VectorSum	(std::vector<double>& x, std::vector<double> const & y) {
		for (int i(0); i < y.size(); i++) {
			x[i] += y[i];
		}
	}

	void VectorMul(std::vector<double>& y, double x) {
		for (int i(0); i < y.size(); i++) {
			y[i] *= x;
		}
	}

	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, double h) {
		std::vector<double> equation(y);
		std::vector<double> K(y.size());
		double sum(0);
		int q(1), p(1);
		for (int i(0); i < 4; i++) {
			VectorMul(K, sum);
			VectorSum(K, y);
			K = (Func(x + sum, K, 1));
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

	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
		std::vector<double> yTemp, newY(y);
		double newX = x;
		int size = ((xEnd - x) + h * 0.1) / h;
		for (int i(0); i < size; i++) {
			yTemp = TemplateFunc(newX, newY, h);


			newX += h;
			newY = yTemp;
			list.push_back(newY);
		}
	}
public:
	Runge_Kutta_4(double X0, double Xn, double h, std::vector<double> Y ,double e, std::function<double(double, std::vector<double>, double)> func)
	: Euler(X0, Xn, h, Y, e, func) 
	{
		
	}

	
};

