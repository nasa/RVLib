/** Unweighted Object - Implementation
 *	
 *	@file 		Unweighted Sample Class
 *    
 *	@brief 		Unweighted Sample Class - Class used for storing and accessing a vector of 
 * 				values(double) representing data with uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 28, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <numeric>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "Unweighted.h"
#include "Weighted.h"

// *------------------------------* 
// |   CONSTRUCTORS/DESTRUCTORS   |
// *------------------------------*

Unweighted::Unweighted(const RandomVariable::vector_type& v) : data(v) {}

Unweighted::Unweighted(const RandomVariable::pvector_type& v) {
	std::for_each(v.cbegin(), v.cend(), [&](const f_pair& p){ data.insert(end(), p.second, p.first); });
}

Unweighted::~Unweighted(){}

// *------------------------------* 
// |          ACCESSORS           |
// *------------------------------*

void Unweighted::set(const size_type k, const double d) {
	data.at(k) = d;
}

double Unweighted::get(const size_type k) const {
	return data.at(k);
}

void Unweighted::append(const double d) {
	data.push_back(d);
}

RandomVariable::pvector_type Unweighted::getWData() const {
	Weighted w(data);
	return w.getWData();
}

// *------------------------------* 
// |         CALCULATIONS         |
// *------------------------------*

double Unweighted::mean() const {
	return accumulate(cbegin(), cend(), 0.0) / data.size();
}

	
double Unweighted::median() const {
	if (data.size() % 2 == 0) {
		return (data.at(data.size() / 2) + data.at(data.size() / 2 + 1)) / 2;	
	}
	return data.at(data.size() / 2);
}

double Unweighted::meanHeight() const {
	pvector_type samples = getWData();
	const auto function = [](const double lhs, const f_pair& rhs){ return lhs + rhs.second; };
	return std::accumulate(samples.cbegin(), samples.cend(), 0.0, function) / static_cast<double>(data.size());
}

double Unweighted::std() const {
    const double dMean = mean(); 
	const auto function = [=](const double lhs, const double rhs) { return lhs + pow((rhs - dMean), 2); };
	return sqrt(std::accumulate(cbegin(), cend(), 0.0, function) / static_cast<double>(data.size()-1));
}

double Unweighted::mode() const {
	vector_type tmp = data;
	std::sort(tmp.begin(), tmp.end());
	vector_type modes;
	const_vtype_iterator cit = tmp.cbegin();

	double runValue = *cit++;
	unsigned int runCount = 1;
	unsigned int highestRunCount = runCount;
	modes.push_back(runValue);

	while (cit != tmp.cend()) {
		if (isDoubleEqual(runValue, *cit)) {                      // run continuing.
			if (++runCount > highestRunCount) {     // current run is new high?
				highestRunCount = runCount;
				if (!isDoubleEqual(modes.front(), runValue)) {   
					modes.clear();
					modes.push_back(runValue);
				}
			}
			else if (runCount == highestRunCount) { // more than one mode, currently
				modes.push_back(runValue);
			}
		}
		else {                                       // new run beginning
			runValue = *cit, runCount = 0;
		}
		++cit;
	}
	return modes[0];
}

// *------------------------------* 
// |           SAMPLING           |
// *------------------------------*

double Unweighted::sampleSingle() const {
	static unsigned int count = 0;
	return get(count++ % data.size());
}

RandomVariable::vector_type Unweighted::sample(unsigned int n) const {
	vector_type samples(n);
	static unsigned int count = 0;
	for (unsigned int i = 0; i < n; i++) {
		samples.push_back(get(count++ % static_cast<unsigned int>(data.size())));
	}
	return samples;
}

double Unweighted::sampleSingleIcdf(const double y) const {
	throw "Unimplemented method";
	return y;
}

RandomVariable::vector_type Unweighted::sampleIcdf(const unsigned int n, const vector_type& v) const {
	throw "Unimplemented method";
	return {static_cast<double>(n), static_cast<double>(v.size())};
}

// *------------------------------* 
// |           VISUAL             |
// *------------------------------*

void Unweighted::printData() const {
	vector_type tmp = data;
	std::sort(tmp.begin(), tmp.end()); 
	const auto function = [](const double val){ std::cout << val << std::endl; };
	std::for_each(tmp.cbegin(), tmp.cend(), function);
}
