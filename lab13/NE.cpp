#include "NE.h"

double NE::CalculateMPD_C() {
	return (Interval[0] + Interval[1]) / 2;
}

void NE::SetValue(double a, double b) {
	Interval[0] = a;
	Interval[1] = b;
}

std::vector<double> const& NE::GetInterval() {
	return Interval;
}

double NE::CalculateHord_C() {
	//return (Interval[0] * Func(Interval[1]) - Interval[1] * Func(Interval[0])) / (Func(Interval[1]) - Func(Interval[0]));
	//((y' * b - y' * a) + (a * fb) - (b * fa)) / (fb + fa)
	return ((dAbscissa * Interval[1] - dAbscissa * Interval[0]) + 
		(Interval[0] * Func(Interval[1]) - Interval[1] * Func(Interval[0]))) / (Func(Interval[1]) - Func(Interval[0]));
}

void NE::MPD(double eps, bool isMod) {
	double C , e;
	int i(0);
	//std::cout.precision(eps);
	std::function<double(NE&) > PtrFunc = &NE::CalculateMPD_C;
	if (isMod) {
		PtrFunc = &NE::CalculateHord_C;
	}

	int count(1);
	do {
		//std::cout<< std::fixed << Interval[0] << " * " << Func(Interval[1]) << " - " << Interval[1] << " * " << Func(Interval[0]) << " / " << Func(Interval[1]) << " - " << Func(Interval[0]) << '\n';

		std::cout << "i - " << i << "\n";
		std::cout << std::fixed << "func(left): " << Func(Interval[0]) << " func(right): " << Func(Interval[1]) << '\n';

		std::cout << count++ << ") (" << Interval[0] << " : " << Interval[1] << "),  ";
		C = PtrFunc(*this);
		std::cout << "C = " << C << ",  " << (Func(Interval[0]) - dAbscissa)  << " * " << Func(C) << " ";
                               
		//i = ((Func(Interval[i]) - dAbscissa) * (Func(C) - dAbscissa) < 0) ? 1 - i : i;
		i = ((Func(Interval[0]) - dAbscissa) * (Func(C) - dAbscissa) < 0) ? 1 : 0;


		Interval[i] = C;
		e = abs(Interval[1] - Interval[0]) / 2;
		std::cout << "e = " << e << "\n\n";

	} while (e > eps);
	std::cout << "C = " << C << "\n";
	std::cout << "e = " << e << " < eps:" << eps << "\n\n";
}

double NE::MPD1(double eps, bool isMod) {
	double C, e;
	int i(0);

	std::function<double(NE&) > PtrFunc = &NE::CalculateMPD_C;
	if (isMod) {
		PtrFunc = &NE::CalculateHord_C;
	}
	int count(1);
	do {
		//std::cout << Interval[0] << " * " << Func(Interval[1]) << " - " << Interval[1] << " * " << Func(Interval[0]) << " / " << Func(Interval[1]) << " - " << Func(Interval[0]) << '\n';

		//std::cout << "i - " << i << "\n";
		//std::cout << std::fixed << "func(left): " << Func(Interval[0]) << " func(right): " << Func(Interval[1]) << '\n';

		//std::cout << count++ << ") (" << Interval[0] << " : " << Interval[1] << "),  ";
		C = PtrFunc(*this);
		//std::cout << "C = " << C << ",  ";
		//std::cout << " (" << (Func(Interval[i]) - dAbscissa) << ") * (" << (Func(C) - dAbscissa) << ") ";
		//i = ((Func(Interval[i]) - dAbscissa) * (Func(C) - dAbscissa) < 0) ? 1 - i : i;
		//i = ((Func(Interval[0]) - dAbscissa) * (Func(C) - dAbscissa) < 0) ? 1 : 0;
		i = ((Func(Interval[0]) - dAbscissa) * (Func(C) - dAbscissa) < 0) ? 1 : 0;



		Interval[i] = C;
		e = abs(Interval[1] - Interval[0]) / 2;
		//std::cout << "e = " << e << "\n\n";	

	} while (e > eps);
	//std::cout << "C = " << C << "\n";
	//std::cout << "e = " << e << " < eps:" << eps << "\n\n";
	return C;
}