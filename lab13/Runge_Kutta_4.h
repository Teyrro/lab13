#pragma once
#include "DE.h"

class Runge_Kutta_4 : public Euler {
protected:
	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, double h);
	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list);
public:
	Runge_Kutta_4(double X0, double Xn, double h, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func, int prec)
		: Euler(X0, Xn, h, Y, e, func, prec)
	{
		realEps = 15 * eps;
	}
	Runge_Kutta_4(){}


};