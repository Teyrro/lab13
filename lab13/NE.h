#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <functional>
#include "DE.h"


class NE {
	std::vector<double> Interval;
	std::function<double(double)> Func;
	double dAbscissa;
	double answer;
public:

	NE(std::string filename, std::function<double(double)> Func) : Interval(2), Func(Func) {
		std::ifstream data(filename);
		data >> Interval[0];
		data >> Interval[1];
	}
	NE(double leftBorder, double rightBorder, std::function<double(double)> Func, double dAbscissa)
		: Interval(2), Func(Func), dAbscissa(dAbscissa)
	{
		std::cout.precision(10);
		Interval[0] = leftBorder;
		Interval[1] = rightBorder;
	}

	double GetAnswer() {
		return answer;
	}

	void SetValue(double a, double b);
	std::vector<double> const& GetInterval();

	void MPD(double eps, bool isMod);
	double MPD1(double eps, bool isMod);
	double CalculateMPD_C();
	double CalculateHord_C();

};