#pragma once
#include <functional>
#include <vector>

class KortewegDeVries
{
private:
	int m_numberOfSpaceCoordinatePoints{};
	// height of the water surface
	std::vector<double> m_eta;
	// velocity of the water surface
	std::vector<double> m_velocity;
	// acceleration of the water surface
	std::vector<double> m_acceleration;

	// constant
	// time interval
	double m_timeInterval{};
	// space interval
	double m_spaceInterval{};

	void initializeWave(std::function<double(double, double)>& initialWave);

public:
	// initialWave returns the wave height with the argument as (time coordinate, space coordinate) 
	KortewegDeVries(int numberOfSpaceCoordinatePoints, std::function<double(double, double)>& initialWave, double timeInterval = 0.1, double spaceInterval = 0.1);
	
	const std::vector<double>& getWaveHeight() const;
};