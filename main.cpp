#include "KortewegDeVries.h"
#include <iostream>

int main()
{
	KortewegDeVries kdv(100);
	for (int count{ 0 }; count < 10; ++count)
	{
		std::cout << kdv << '\n';
		kdv.stepForward();
	}

	return 0;
}