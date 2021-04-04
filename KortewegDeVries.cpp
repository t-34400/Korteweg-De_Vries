#include "KortewegDeVries.h"

KortewegDeVries::KortewegDeVries(int numberOfSpaceCoordinatePoints, const std::function<double(double, double)>& initialWave, double timeInterval, double spaceInterval)
	:m_numberOfSpaceCoordinatePoints{ numberOfSpaceCoordinatePoints }, m_timeInterval{ timeInterval }, m_spaceInterval{ spaceInterval }
{
	// allocate the memory
	m_height.reserve(m_numberOfSpaceCoordinatePoints);
	m_velocity.reserve(m_numberOfSpaceCoordinatePoints);
	
	// initialize wave
	initializeWave(initialWave);
}

void KortewegDeVries::initializeWave(const std::function<double(double, double)>& initialWave)
{
	double spaceCoordinate{ 0.0 };
	for (int point{ 0 };point<m_numberOfSpaceCoordinatePoints;++point)
	{
		// set the initial wave height
		m_height[point] = initialWave(0, spaceCoordinate);
		// set the initial wave velocity using central difference
		m_velocity[point] = (initialWave(m_timeInterval, spaceCoordinate) - initialWave(-m_timeInterval, spaceCoordinate)) * 0.5 / m_timeInterval;
		
		spaceCoordinate += m_spaceInterval;
	}
}

void KortewegDeVries::stepForward(int steps)
{
	double nextEta{};
	double nextVelocity{};

	for (int step{ 0 }; step < steps; ++step)
	{
		for (int point{ 0 }; point < m_numberOfSpaceCoordinatePoints; ++point)
		{
			nextEta = m_height[point] + m_velocity[point] * m_timeInterval;
			nextVelocity = m_height[point] * getFirstOrderSpatialCentralDifference(point) + getThirdOrderSpatialCentralDifference(point);
		}
	}

}

double KortewegDeVries::getFirstOrderSpatialCentralDifference(int point) const { return (m_height[next(point)] - m_height[prev(point)]) * 0.5 / m_spaceInterval; }
double KortewegDeVries::getThirdOrderSpatialCentralDifference(int point) const
{
	return (m_height[next(point, 3)] - 3 * m_height[next(point)] + 3 * m_height[prev(point)] + m_height[prev(point, 3)]) * 0.125 / (m_spaceInterval * m_spaceInterval * m_spaceInterval);
}

const std::vector<double>& KortewegDeVries::getWaveHeight() const { return m_height; }