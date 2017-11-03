/** Weighted Object - Implementation
 *	
 *	@file 		Weighted Sample Class
 *    
 *	@brief 		Weighted Sample Class - Class used for storing and accessing a vector of 
 * 				values(double) and their frequencies(unsigned int) representing data with uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		July 25, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <numeric>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string> 

#include "Weighted.h"

// *------------------------------* 
// |   CONSTRUCTORS/DESTRUCTORS   |
// *------------------------------*

Weighted::Weighted() {
	size = 0;
}

Weighted::Weighted(RandomVariable::vector_type v) {
	size = v.size();
	if (size > 0) {
		std::sort(v.begin(), v.end());
		double prev = v.at(0);
		data.push_back(std::make_pair(prev, 0));
		// Create weighted sample set (vector_type of pairs)
		for (double const & x : v) {
			if (!isDoubleEqual(prev, x)) {
				prev = x;
				// Create a new entries for a different double value
				data.push_back(std::make_pair(prev, 0));
			}
			// The current double value frequency is incremented if a new value is encountered
			// or the same value
			data.back().second++;
		}
	}
}

Weighted::Weighted(const RandomVariable::pvector_type& v) {
	data = v;
	// Lambda function that adds up frequencies (second value in the std::pair) of double values to get size
	auto function = [](const unsigned int lhs, const f_pair & rhs){ return lhs + rhs.second; };
	size = static_cast<size_type>(std::accumulate(v.begin(), v.end(), 0, function));
}

Weighted::~Weighted(){}

// *------------------------------* 
// |           ACCESSORS          |
// *------------------------------*

void Weighted::set(const size_type k, const RandomVariable::f_pair p) {
	size += p.second - data.at(k).second;
	data.at(k) = p;
}

void Weighted::setFreq(const double d, const size_type freq) { 			    
	// returns iterator pointing to matching object
	ptype_iterator it = findValPtr(d);
	// std::find_if() returns end() if the condition is never satisfied
	if (it == end()) {
		throw std::invalid_argument("Value not found in the data set");
	}
	// add or decrease total count based on assignment
	size += freq - it->second;
	it->second = freq;
}

RandomVariable::f_pair Weighted::getPair(const size_type k) const {
	return data.at(k);
}

double Weighted::get(const size_type k) const {
	unsigned int i = 0;
	unsigned int sum = 0;
	// Counting how many total place from initial element
	while (k >= sum) {
		sum += data.at(i++).second;	
	}
	if (i != 0) {
		i--;
	}
	return data.at(i).first;
}

Weighted::ptype_iterator Weighted::findValPtr(const double val) {
	return std::find_if(begin(), end(), [=](const f_pair& obj){ return isDoubleEqual(obj.first, val); });
}

Weighted::const_ptype_iterator Weighted::findValPtr(const double val) const {
	return std::find_if(cbegin(), cend(), [=](const f_pair& obj){ return isDoubleEqual(obj.first, val); });
}

void Weighted::append(const RandomVariable::f_pair p) {
	ptype_iterator it = findValPtr(p.first);
	if (it == cend()) {
		data.push_back(p);
	} else {
		it->second += p.second;
	}
	size += p.second;
}

void Weighted::append(const double d) {
	ptype_iterator it = findValPtr(d);
	if (it == end()) {
		data.push_back(std::make_pair(d, 1));
	} else {
		it->second++;
	}
	size++;
}

Weighted::vector_type Weighted::getData() const {
	vector_type samples;
	// creates an unweighted sample set from a weighted sample set
	std::for_each(cbegin(), cend(), [&](const f_pair& p){ samples.insert(samples.end(), p.second, p.first); });
	return samples;
}

// *------------------------------* 
// |         CALCULATIONS         |
// *------------------------------*

double Weighted::mean() const {
    const auto function = [](const double lhs, const f_pair& rhs){ return lhs + rhs.first * rhs.second; };
	return std::accumulate(cbegin(), cend(), 0.0, function) / static_cast<double>(size);
}

double Weighted::median() const {
	if (size % 2 == 0) {
		return (data.at(size / 2).first + data.at(size / 2 + 1).first) / 2;	
	}
	return data.at(size / 2).first;
}

double Weighted::meanHeight() const {
    const auto function = [](const unsigned int lhs, const f_pair& rhs){ return lhs + rhs.second; };
	return std::accumulate(cbegin(), cend(), 0.0, function) / static_cast<int>(size);
}

double Weighted::std() const {
    const double dMean = mean(); 
	const vector_type samples = getData();
    const auto function = [=](const double lhs, const double rhs){ return lhs + pow((rhs - dMean), 2); };
	return sqrt(std::accumulate(samples.cbegin(), samples.cend(), 0.0, function) / static_cast<double>(size));
}

double Weighted::mode() const {
	pvector_type modes;
	modes.push_back(std::make_pair(0, 0));
	for (const_ptype_iterator pcit = cbegin(); pcit != cend(); pcit++) {
		if (pcit->second > modes[0].second) {
			modes.clear();
			modes.push_back(*pcit);
		} else if (pcit->second == modes[0].second) {
			modes.push_back(*pcit);
		}
	}
	return modes[0].first;
}

// *------------------------------* 
// |          SAMPLING            |
// *------------------------------*

double Weighted::sampleSingle() const {
	static unsigned int count = 0;
	return get(count++ % size);
}

RandomVariable::vector_type Weighted::sample(const unsigned int n) const {
	vector_type samples(n);
	static unsigned int count = 0;
	for (unsigned int i = 0; i < n; i++) {
		samples.push_back(get(count++ % size));
	}
	return samples;
}

double Weighted::sampleSingleIcdf(const double y) const {
	return y;
}

RandomVariable::vector_type Weighted::sampleIcdf(const unsigned int n, const vector_type& v) const {
	return {static_cast<double>(n), static_cast<double>(v.size())};
}

// *------------------------------* 
// |           VISUAL             |
// *------------------------------*

void Weighted::printData() const {
	std::for_each(cbegin(), cend(), [](const f_pair& p){ std::cout << p.first << " : " << p.second << std::endl; });
}

