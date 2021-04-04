#pragma once
#include <functional>
#include <vector>

class KortewegDeVries
{
private:
	int m_numberOfSpaceCoordinatePoints{};
	// height of the water surface
	std::vector<double> m_height;
	// velocity of the water surface
	std::vector<double> m_velocity;

	// constant
	// time interval
	double m_timeInterval{};
	// space interval
	double m_spaceInterval{};

	void initializeWave(const std::function<double(double, double)>& initialWave);
	double getFirstOrderSpatialCentralDifference(int point) const;
	double getThirdOrderSpatialCentralDifference(int point) const;

	inline int prev(int point, int n = 1) const
	{
		return (point - n + m_numberOfSpaceCoordinatePoints) % m_numberOfSpaceCoordinatePoints;
	}

	inline int next(int point, int n = 1) const
	{
		return (point + n) % m_numberOfSpaceCoordinatePoints;
	}

	// soliton solution of KdV equation
	static double solitonSolution(double time, double space);

public:
	// initialWave returns the wave height with the argument as (time coordinate, space coordinate) 
	KortewegDeVries(int numberOfSpaceCoordinatePoints, const std::function<double(double, double)>& initialWave = solitonSolution, double timeInterval = 0.1, double spaceInterval = 0.1);
	
	void stepForward(int steps = 1);

	const std::vector<double>& getWaveHeight() const;
};