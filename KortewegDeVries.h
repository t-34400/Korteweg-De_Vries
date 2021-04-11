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
	// the height and the vertical velocity of the water surface
	VectorStorage m_height;

	// constant
	// time interval
	const double m_timeInterval{};
	// space interval
	const double m_spaceInterval{};

	void initializeWave(const std::function<double(double)> initialWave);
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
	explicit KortewegDeVries(std::size_t maxIndex, const std::function<double(double)> initialWave = nullptr, double timeInterval = 0.001, double spaceInterval = 0.1);
	
	void stepForward(int steps = 1);

	int getmaxIndex() const;
	const VectorStorage& getHeight() const;
	VectorStorage getTimeDerivatives(double time, const VectorStorage& height) const;
	
	friend std::ostream& operator<< (std::ostream& out, KortewegDeVries& kdv);
};