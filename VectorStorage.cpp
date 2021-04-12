#pragma once
#include "VectorStorage.h"
#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>

VectorStorage::VectorStorage(int n) :m_value(n)
{
}

VectorStorage::VectorStorage(const std::vector<double>& vector) :m_value(vector)
{
}

VectorStorage::VectorStorage(const std::initializer_list<double>& list) : VectorStorage()
{
	auto iter{ list.begin() };
	auto endIter{ list.end() };

	for (auto& element : m_value)
	{
		if (iter != endIter)
		{
			element = *iter;
			++iter;
		}
		else
		{
			element = 0.0;
		}
	}
}


VectorStorage operator-(const VectorStorage& p)
{
	// the vector of the VectorStorage object which will be returned
	std::vector<double> returnVector(p.getVector());

	for (auto& element : returnVector)
	{
		element = -element;
	}
	return { returnVector };
}

VectorStorage operator+(const VectorStorage& p1, const VectorStorage& p2)
{
	VectorStorage returnVectorStorage(p1);
	returnVectorStorage += p2;
	return returnVectorStorage;
}

VectorStorage operator-(const VectorStorage& p1, const VectorStorage& p2)
{
	return p1 + (-p2);
}

VectorStorage operator*(const VectorStorage& p, double d)
{
	// the vector of the VectorStorage object which will be returned
	VectorStorage returnVectorStorage(p);
	returnVectorStorage *= d;
	return returnVectorStorage;
}

VectorStorage operator*(double d, const VectorStorage& p) { return p * d; }

double operator*(const VectorStorage& p1, const VectorStorage& p2)
{
	const std::size_t maxIndex{ p1.getDimension() };
	double returnValue{ 0.0 };
	for (std::size_t index{ 0 }; index < maxIndex; ++index)
	{
		returnValue += p1[index] * p2[index];
	}

	return { returnValue };
}

VectorStorage& VectorStorage::operator+=(const VectorStorage& p)
{
	int index{ 0 };
	for (auto& element : p)
	{
		m_value[index] += element;
		++index;
	}

	return *this;
}

VectorStorage& VectorStorage::operator-=(const VectorStorage& p)
{
	*this += (-p);
	return *this;
}

VectorStorage& VectorStorage::operator*=(double d)
{
	for (auto& element : m_value)
	{
		element *= d;
	}
	return *this;
}

double& VectorStorage::operator[](int index) { return m_value[index]; }

const double& VectorStorage::operator[](int index) const { return m_value[index]; }

bool VectorStorage::operator==(const VectorStorage& p) const
{
	return (m_value == p.m_value);
}

std::ostream& operator<<(std::ostream& out, const VectorStorage& p)
{
	for (auto element : p)
		out << element << ' ';
	return out;
}

std::size_t VectorStorage::getDimension() const { return m_value.size(); }
const std::vector<double>& VectorStorage::getVector() const { return m_value; }
double VectorStorage::getSquareMagnitude() const { return (*this) * (*this); }
double VectorStorage::getMagnitude() const { return std::sqrt(getSquareMagnitude()); }

std::vector<double>::const_iterator VectorStorage::begin() const { return m_value.begin(); }
std::vector<double>::const_iterator VectorStorage::end() const { return m_value.end(); }
std::vector<double>::const_reverse_iterator VectorStorage::rbegin() const { return m_value.rbegin(); }
std::vector<double>::const_reverse_iterator VectorStorage::rend() const { return m_value.rend(); }

std::vector<double>::iterator VectorStorage::begin() { return m_value.begin(); }
std::vector<double>::iterator VectorStorage::end() { return m_value.end(); }
std::vector<double>::reverse_iterator VectorStorage::rbegin() { return m_value.rbegin(); }
std::vector<double>::reverse_iterator VectorStorage::rend() { return m_value.rend(); }