#include "KortewegDeVries.h"
#include <cassert>
#include <cmath>

KortewegDeVries::KortewegDeVries(int maxIndex, const std::function<double(double, double)> initialWave, double timeInterval, double spaceInterval)
	:m_maxIndex{ maxIndex }, m_timeInterval{ timeInterval }, m_spaceInterval{ spaceInterval }
{
	assert(m_maxIndex > 0);

	// allocate the memory
	m_height.resize(m_maxIndex);
	m_velocity.resize(m_maxIndex);
	
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

void KortewegDeVries::initializeWave(const std::function<double(double, double)> initialWave)
{
	double spaceCoordinate{ 0.0 };
	for (int point{ 0 };point<m_maxIndex;++point)
	{
		// set the initial wave height
		m_height[point] = initialWave(0, spaceCoordinate);
		// set the initial wave velocity using central difference
		m_velocity[point] = (initialWave(m_timeInterval, spaceCoordinate) - initialWave(-m_timeInterval, spaceCoordinate)) * 0.5 / m_timeInterval;
		
		spaceCoordinate += m_spaceInterval;
	}
}

void KortewegDeVries::initializeWaveToSoliton()
{
	// the center point of the system
	double centerPoint{ 0.5 * m_spaceInterval * m_maxIndex };

	auto soliton{ [centerPoint](double time, double space)
		{
			// bring the wave peak to the center of the system
			space -= centerPoint;

			// if we only use the following statement, the wave peak will be space = 0
			double sqrtOfDenominator{ std::cosh(3 * space - 36 * time) + 3 * std::cosh(space - 28 * time) };
			return 12 * (3 + 4 * std::cosh(2 * space - 8 * time) + std::cosh(4 * space - 64 * time)) / (sqrtOfDenominator * sqrtOfDenominator);
		} };
	initializeWave(soliton);
}

void KortewegDeVries::stepForward(int steps)
{
	double nextHeight{};
	double nextVelocity{};

	for (int step{ 0 }; step < steps; ++step)
	{
		for (int point{ 0 }; point < m_maxIndex; ++point)
		{
			nextHeight = m_height[point] + m_velocity[point] * m_timeInterval;
			nextVelocity = -6 * m_height[point] * getFirstOrderSpatialCentralDifference(point) - getThirdOrderSpatialCentralDifference(point);

			m_height[point] = nextHeight;
			m_velocity[point] = nextVelocity;
		}
	}

}

// **Warning** 
double KortewegDeVries::getFirstOrderSpatialCentralDifference(int point) const { return (m_height[next(point)] - m_height[prev(point)]) * 0.5 / m_spaceInterval; }
double KortewegDeVries::getThirdOrderSpatialCentralDifference(int point) const
{
	return (m_height[next(point, 2)] - 2 * m_height[next(point)] + 2 * m_height[prev(point)] - m_height[prev(point, 2)]) * 0.5 / (m_spaceInterval * m_spaceInterval * m_spaceInterval);
}

int KortewegDeVries::getmaxIndex() const { return m_maxIndex; }
const std::vector<double>& KortewegDeVries::getWaveHeight() const { return m_height; }

std::ostream& operator<< (std::ostream& out, KortewegDeVries& kdv)
{
	for (auto height : kdv.m_height)
	{
		out << height << ' ';
	}
	return out;
}