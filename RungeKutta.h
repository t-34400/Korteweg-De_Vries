#pragma once
#include <functional>
#include <initializer_list>
#include <vector>

namespace RungeKutta
{
	// V is the type of variables which must be used operator+(V) or operator*(double) and returns vector sum or scalar multiple
	// F is the type of the function to calculate the time derivative of variables which has the argument (double, V) and returns V
	template <typename V>
	V RK4(double time, const V& variables, std::function<V(double, const V&)>& getTimeDerivatives, double timeStep)
	{
		static constexpr double fraction{ 1.0 / 6.0 };
		double halfStepForward{ time + timeStep * 0.5 };

		V k1{ getTimeDerivatives(time, variables) * timeStep };
		V k2{ getTimeDerivatives(halfStepForward, variables + k1 * 0.5) * timeStep };
		V k3{ getTimeDerivatives(halfStepForward, variables + k2 * 0.5) * timeStep };
		V k4{ getTimeDerivatives(time + timeStep, variables + k3) * timeStep };

		return variables + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * fraction;
	}


	template <class T, typename V>
	V RK4(double time, const V& variables, std::function<V(T, double, const V&)>& getTimeDerivatives, double timeStep)
	{
		static constexpr double fraction{ 1.0 / 6.0 };
		double halfStepForward{ time + timeStep * 0.5 };

		V k1{ getTimeDerivatives(T, time, variables) * timeStep };
		V k2{ getTimeDerivatives(T, halfStepForward, variables + k1 * 0.5) * timeStep };
		V k3{ getTimeDerivatives(T, halfStepForward, variables + k2 * 0.5) * timeStep };
		V k4{ getTimeDerivatives(T, time + timeStep, variables + k3) * timeStep };

		return variables + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * fraction;
	}
}