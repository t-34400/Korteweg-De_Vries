#pragma once
#include <functional>
#include <iostream>
#include <vector>

class KortewegDeVries
{
private:
	int m_maxIndex{};
	// height of the water surface
	std::vector<double> m_height;
	// velocity of the water surface
	std::vector<double> m_velocity;

	// constant
	// time interval
	double m_timeInterval{};
	// space interval
	double m_spaceInterval{};

	void initializeWave(const std::function<double(double, double)> initialWave);
	// initialize the wave to soliton solution of KdV equation (P.D.Lax solution) when user didn't provide the initial wave
	void initializeWaveToSoliton();

	double getFirstOrderSpatialCentralDifference(int point) const;
	double getThirdOrderSpatialCentralDifference(int point) const;

	inline int prev(int point, int n = 1) const
	{
		return (point - n + m_maxIndex) % m_maxIndex;
	}

	inline int next(int point, int n = 1) const
	{
		return (point + n) % m_maxIndex;
	}


public:
	// initialWave returns the wave height with the argument as (time coordinate, space coordinate) 
	KortewegDeVries(int maxIndex, const std::function<double(double, double)> initialWave = nullptr, double timeInterval = 0.001, double spaceInterval = 0.1);
	
	void stepForward(int steps = 1);

	int getmaxIndex() const;
	const std::vector<double>& getWaveHeight() const;

	friend std::ostream& operator<< (std::ostream& out, KortewegDeVries& kdv);
};