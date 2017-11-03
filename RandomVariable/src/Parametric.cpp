/** Parametric Object - Implementation
 *	
 *	@file 		(Abstract) Parametric Distribution Class
 *    
 *	@brief 		Parametric Distribution Class - Skeleton class declarations for a parametric distribution class representing 
 *				value uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		August 11, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <stdexcept>
#include <algorithm>

#include "Parametric.h"

double Parametric::sampleSingle() const {
	return sample(1)[0];
}

RandomVariable::vector_type Parametric::sampleIcdf(const unsigned int n, const RandomVariable::vector_type& v) const {
	if (n != v.size()) {
		throw std::invalid_argument("Size of value vector must be equal to size integer argument");
	}
	vector_type samples;
	// calculates Icdf() for each value in the v vector and stores it in samples
	// [=] signals that the lambda function can throw away each value after returning
	std::transform(v.begin(), v.end(), samples.begin(), [=](double prob) { return icdf(prob); });
	return samples;
}

double Parametric::sampleSingleIcdf(const double P) const {
	return icdf(P);
}

Parametric::~Parametric(){}
