#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <functional>
#include <iomanip>

class Euler {
protected:
	double x, xEnd, h, tmpH, eps, realEps, prec;
	int index, stepCount;
	std::vector<double> y;
	std::list<std::vector<double>> list;
	std::function<double(double, std::vector<double>, double)> MoreFunc;


	void PrintList(std::list<std::vector<double>> const& list);
	void PrintList(std::list<std::vector<double>> const& list, double x);
	void PrintY(std::vector<double> y);
	void PrintY(std::vector<double> y, double x);


	void VectorSum(std::vector<double>& x, std::vector<double> const& y);
	void VectorMul(std::vector<double>& y, double x);

	std::vector<double> Func(double x, std::vector<double> equation, double step);
	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, double h);

	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list);
	void DeleteUnusefullValue(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp);
	bool Compare(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp);

public:
	Euler(double X0, double Xn, double h, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func, int prec)
	: x(X0), xEnd(Xn), y(Y), h(h), tmpH(h), eps(e), MoreFunc(func), realEps(3 * eps), prec(prec)
	{
		std::cout.precision(prec+1);

		for (int i(0); i < Y.size(); i++) {
			if (Y[i] == -111) {
				index = i;
				break;
			}
		}
	}

	Euler() {}

	double F(double x);
	void NEForFindingK(double nextValueX, double nextValueY1);

	virtual void FindAnswer();
};

//class Miln : Runge_Kutta_4 {
//	void MilnFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list) {
//		std::vector<double> yTemp, yi, newY(y);
//		double newX = x;
//		int size = ((xEnd - x) + h * 0.1) / h;
//		for (int i(3); i < size; i++) {
//			//yTemp = TemplateTemplateFunc(newX, newY, h);
//
//			//std::cout << "x = " << x << "\n";
//			//PrintY(y);
//			//std::cout << " + ";
//			//PrintY(Func(x, y, 1));
//			//std::cout << " * " << h << " = ";
//			//PrintY(yTemp);
//			//std::cout << "\n\n";
//
//			newX += h;
//			newY = yTemp;
//			list.push_back(newY);
//		}
//	}
//
//	std::vector<double> TemplateTemplateFunc(double x, std::vector<double> y, int index, std::list<std::vector<double>>& list, double h) {
//		std::vector<double> equation(y);
//		std::vector<double> tmpEquation(Func(x, equation, h));
//		auto it = list.begin();
//		for (it; it != list.end(); it++) {
//			
//			
//		}
//		return equation;
//	}
//
//	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list, int size) {
//		std::vector<double> yTemp, newY(y);
//		double newX = x;
//		for (int i(0); i < size; i++) {
//
//
//			yTemp = TemplateFunc(newX, newY, h);
//
//			//std::cout << "x = " << x << "\n";
//			//PrintY(y);
//			//std::cout << " + ";
//			//PrintY(Func(x, y, 1));
//			//std::cout << " * " << h << " = ";
//			//PrintY(yTemp);
//			//std::cout << "\n\n";
//
//			newX += h;
//			newY = yTemp;
//			list.push_back(newY);
//		}
//	}
//public:
//	Miln(double X0, double Xn, double h, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func)
//		: Runge_Kutta_4(X0, Xn, h, Y, e, func) {
//		if (((xEnd - x) + h * 0.1) / h < 3)
//			throw;
//	}
//
//	virtual void FindAnswer() {
//		std::list<std::vector<double>> listTemp(list);
//		double factor(1);
//		int size = ((xEnd - x) + h * 0.1) / h;
//		MethodFA(y, h, list, 3);
//		do {
//			h /= 2;
//			std::cout << "h = " << h << "\n";
//			MethodFA(y, h, listTemp, size);
//
//			std::cout << "Size list " << list.size() << ", Size listH/2 " << listTemp.size() << "\n";
//			//PrintY(y);
//		} while (Compare(list, listTemp));
//	}
//
//};
