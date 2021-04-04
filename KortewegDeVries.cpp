#include "KortewegDeVries.h"

KortewegDeVries::KortewegDeVries(int numberOfSpaceCoordinatePoints, std::function<double(double, double)>& initialWave, double timeInterval, double spaceInterval)
	:m_numberOfSpaceCoordinatePoints{ numberOfSpaceCoordinatePoints }, m_timeInterval{ timeInterval }, m_spaceInterval{ spaceInterval }
{
	// allocate the memory
	m_eta.reserve(m_numberOfSpaceCoordinatePoints);
	m_velocity.reserve(m_numberOfSpaceCoordinatePoints);
	m_acceleration.reserve(m_numberOfSpaceCoordinatePoints);
	
	// initialize wave
	initializeWave(initialWave);
}

void KortewegDeVries::initializeWave(std::function<double(double, double)>& initialWave)
{
	double spaceCoordinate{ 0.0 };
	for (int count{ 0 };count<m_numberOfSpaceCoordinatePoints;++count)
	{
		// set the initial wave height
		m_eta[count] = initialWave(0, spaceCoordinate);
		// set the initial wave velocity using central difference
		m_velocity[count] = (initialWave(m_timeInterval, spaceCoordinate) - initialWave(-m_timeInterval, spaceCoordinate)) * 0.5 / m_timeInterval;
		// set the initial wave acceleration using central difference
		m_acceleration[count] = (initialWave(2 * m_timeInterval, spaceCoordinate) + initialWave(-2 * m_timeInterval, spaceCoordinate) - 2 * m_eta[count]) 
								* 0.25 / (m_timeInterval * m_timeInterval);

		spaceCoordinate += m_spaceInterval;
	}
}

const std::vector<double>& KortewegDeVries::getWaveHeight() const { return m_eta; }