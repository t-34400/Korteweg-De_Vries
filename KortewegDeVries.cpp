#include "KortewegDeVries.h"
#include <cassert>
#include <cmath>
#include <functional>

KortewegDeVries::KortewegDeVries(std::size_t maxIndex, const std::function<double(double)> initialWave, double timeInterval, double spaceInterval)
	:m_maxIndex{ maxIndex }, m_timeInterval{ timeInterval }, m_spaceInterval{ spaceInterval }, m_height(maxIndex)
{
	assert(m_maxIndex > 0);
	
	// initialize wave
	if (initialWave==nullptr)
	{
		// initialize the wave to soliton solution when user didn't provide the initial wave
		initializeWaveToSoliton();
	}
	else
	{
		initializeWave(initialWave);
	}
}

void KortewegDeVries::initializeWave(const std::function<double(double)> initialWave)
{
	double spaceCoordinate{ 0.0 };
	for (int point{ 0 };point<m_maxIndex;++point)
	{
		// set the initial wave height
		m_height[point] = initialWave(spaceCoordinate);

		spaceCoordinate += m_spaceInterval;
	}
}

void KortewegDeVries::initializeWaveToSoliton()
{
	// the center point of the system
	double centerPoint{ 0.5 * m_spaceInterval * m_maxIndex };

	auto soliton{ [centerPoint](double space)
		{
			// bring the wave peak to the center of the system
			space -= centerPoint;

			// if we only use the following statement, the wave peak will be space = 0
			double sqrtOfDenominator{ std::cosh(3 * space) + 3 * std::cosh(space) };
			return 12 * (3 + 4 * std::cosh(2 * space) + std::cosh(4 * space)) / (sqrtOfDenominator * sqrtOfDenominator);
		} };
	initializeWave(soliton);
}

void KortewegDeVries::stepForward(int steps)
{
	for (int step{ 0 }; step < steps; ++step)
	{
		for (int point{ 0 }; point < m_maxIndex; ++point)
		{
			m_height = RungeKutta::RK4(0.0, m_height, getTimeDerivatives, m_timeInterval);
		}
	}

}

double KortewegDeVries::getFirstOrderSpatialCentralDifference(int point) const { return (m_height[next(point)] - m_height[prev(point)]) * 0.5 / m_spaceInterval; }
double KortewegDeVries::getThirdOrderSpatialCentralDifference(int point) const
{
	return (m_height[next(point, 2)] - 2 * m_height[next(point)] + 2 * m_height[prev(point)] - m_height[prev(point, 2)]) * 0.5 / (m_spaceInterval * m_spaceInterval * m_spaceInterval);
}

VectorStorage KortewegDeVries::getTimeDerivatives(double time, const VectorStorage& variables) const
{
	std::size_t index{ 0 };
	VectorStorage returnVariables(variables.getDimension());
	for (auto& element : returnVariables)
	{
		element = -6 * m_height[index] * getFirstOrderSpatialCentralDifference(index) - getThirdOrderSpatialCentralDifference(index);
	}
	return returnVariables;
}

int KortewegDeVries::getmaxIndex() const { return m_maxIndex; }
const VectorStorage& KortewegDeVries::getHeight() const { return m_height; }

std::ostream& operator<< (std::ostream& out, KortewegDeVries& kdv)
{
	for (auto height : kdv.m_height.getVector())
	{
		out << height << ' ';
	}
	return out;
}