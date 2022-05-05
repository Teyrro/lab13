#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <functional>
#include <iomanip>

class Euler {
protected:
	double x, xEnd, h, eps, realEps;
	std::vector<double> y;
	std::list<std::vector<double>> list;
	std::function<double(double, std::vector<double>, double)> MoreFunc;

	void VectorSum(std::vector<double>& x, std::vector<double> const& y);
	void VectorMul(std::vector<double>& y, double x);
	std::vector<double> Func(double x, std::vector<double> equation, double step);
	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, double h);
	void PrintList(std::list<std::vector<double>> const& list);
	void PrintY(std::vector<double> y);
	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list);
	void DeleteUnusefullValue(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp);
	bool Compare(std::list<std::vector<double>>& list, std::list<std::vector<double>>& listTemp);
public:
	Euler(double X0, double Xn, double h, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func, int prec) 
	: x(X0), xEnd(Xn), y(Y), h(h), eps(e), MoreFunc(func), realEps(3 * eps)
	{
		std::cout.precision(prec+1);
	}

	virtual void FindAnswer() {	
		
		std::list<std::vector<double>> listTemp(list);
		double factor(1);
		MethodFA(y, h, list);
		do {
			h /= 2;
			std::cout << "h = " << h << "\n";
			MethodFA(y, h, listTemp);
			//PrintList(listTemp);
		
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
	SimpModEulerT(double X0, double Xn, double n, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func, int prec)
	: Euler(X0, Xn, n, Y, e, func, prec) 
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
	SimpModEulerD(double X0, double Xn, double n, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func, int prec)
	: Euler(X0, Xn, n, Y, e, func, prec) 
	{

	}
};

class Runge_Kutta_4 : public Euler {
protected:
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
	Runge_Kutta_4(double X0, double Xn, double h, std::vector<double> Y ,double e, std::function<double(double, std::vector<double>, double)> func, int prec)
	: Euler(X0, Xn, h, Y, e, func, prec) 
	{
		realEps = 15 * eps;
	}

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
