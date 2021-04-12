#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>

class VectorStorage
{
private:
	std::vector<double> m_value{};

public:
	VectorStorage(int n = 0);
	VectorStorage(const std::vector<double>& vector);
	VectorStorage(const std::initializer_list<double>& list);

	VectorStorage& operator+=(const VectorStorage& p);
	VectorStorage& operator-=(const VectorStorage& p);
	VectorStorage& operator*=(double d);
	double& operator[](int index);
	const double& operator[](int index) const;
	bool operator==(const VectorStorage& p) const;

	std::size_t getDimension() const;
	const std::vector<double>& getVector() const;
	double getSquareMagnitude() const;
	double getMagnitude() const;

	// iterator (const version)
	std::vector<double>::const_iterator begin() const;
	std::vector<double>::const_iterator end() const;
	std::vector<double>::const_reverse_iterator rbegin() const;
	std::vector<double>::const_reverse_iterator rend() const;
	// iterator (non-const version)
	std::vector<double>::iterator begin();
	std::vector<double>::iterator end();
	std::vector<double>::reverse_iterator rbegin();
	std::vector<double>::reverse_iterator rend();
};

VectorStorage operator-(const VectorStorage& p);
VectorStorage operator+(const VectorStorage& p1, const VectorStorage& p2);
VectorStorage operator-(const VectorStorage& p1, const VectorStorage& p2);
VectorStorage operator*(const VectorStorage& p, double d);
VectorStorage operator*(double d, const VectorStorage& p);
double operator*(const VectorStorage& p1, const VectorStorage& p2);
std::ostream& operator<<(std::ostream& out, const VectorStorage& p);