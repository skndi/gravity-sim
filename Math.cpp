#include "Math.h"

double Math::pow(double num, int times) {

	double temp = 1;
	if (times == 0) return 1;

	while (times-- > 0) {

		temp *= num;
	}

	return temp;
}