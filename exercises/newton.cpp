#include <iostream>

double abs(double n) {
	return n > 0 ? n : -1. * n;
}

double sqrt(double n) {
	double guess = n / 2;
	const auto epsilon = 0.0001;

	while (true) {
		guess = 1./2. * (guess + n / guess);
		std::cout << guess << '\n';
		if (abs(guess * guess - n) < 0.0001)
			break;
	}

	std::cout << std::flush;
	return guess;
}

int main() {
	sqrt(42.);
	return 0;
}
