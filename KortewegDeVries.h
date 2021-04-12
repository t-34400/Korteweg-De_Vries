#pragma once
#include "RungeKutta.h"
#include "VectorStorage.h"
#include <functional>
#include <iostream>
#include <vector>

class KortewegDeVries
{
private:
	const std::size_t m_maxIndex{};
	// the height of the water surface
	VectorStorage m_height;

	// constant
	// time interval
	const double m_timeInterval{};
	// space interval
	const double m_spaceInterval{};

	void initializeWave(const std::function<double(double)> initialWave);
	// initialize the wave to soliton solution of KdV equation (P.D.Lax solution) when user didn't provide the initial wave
	void initializeWaveToSoliton();

	double getFirstOrderSpatialCentralDifference(int point, const VectorStorage& variables) const;
	double getThirdOrderSpatialCentralDifference(int point, const VectorStorage& variables) const;

	// indexing operations for the calculation of time derivatives (free end boundary condition)
	inline std::size_t prev(std::size_t point, std::size_t n = 1) const
	{
		if (point < n)
			return 0;
		return point - n;
	}
	inline std::size_t next(std::size_t point, std::size_t n = 1) const
	{
		if (point + n > m_maxIndex-1)
			return m_maxIndex-1;
		return point + n;
	}


public:
	// initialWave returns the wave height with the argument as (time coordinate, space coordinate) 
	explicit KortewegDeVries(std::size_t maxIndex, const std::function<double(double)> initialWave = nullptr, double timeInterval = 0.001, double spaceInterval = 0.1);
	
	void stepForward(int steps = 1);

	int getmaxIndex() const;
	const VectorStorage& getHeight() const;
	
	friend std::ostream& operator<< (std::ostream& out, KortewegDeVries& kdv);
};