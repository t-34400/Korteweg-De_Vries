#include "KortewegDeVries.h"
#include <cmath>
#include <iostream>

int main()
{
	auto sinFucntion{ [](double x) {
			return std::sin(x);
		} };

	KortewegDeVries kdv(100,sinFucntion);
	for (int count{ 0 }; count < 10; ++count)
	{
		std::cout << kdv << '\n';
		kdv.stepForward();
	}

	return 0;
}