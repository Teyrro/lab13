#pragma once
#include "DE.h"

class SimpModEulerT : public Euler {
protected:
	virtual void MethodFA(std::vector<double>& y, double h, std::list<std::vector<double>>& list);
	virtual std::vector<double> TemplateFunc(double x, std::vector<double> y, std::vector<double> newY, double h);
public:
	SimpModEulerT(double X0, double Xn, double n, std::vector<double> Y, double e, std::function<double(double, std::vector<double>, double)> func, int prec)
		: Euler(X0, Xn, n, Y, e, func, prec)
	{

	}
	SimpModEulerT() {}

};