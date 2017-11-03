/**	Lognormal Object - Implementation
 *	
 *	@file 		Lognormal Distribution Class
 *    
 *	@brief 		Lognormal Distribution Class - Class used for storing and accessing a lognormal distribution
 * 				representing data with uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 28, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <random>
#include <cfloat> // DBL_MIN

#include "Lognormal.h"
#include "Normal.h"

//    *-------------------------------------* 
//    |    CONSTRUCTORS AND DESTRUCTORS     |
//    *-------------------------------------*

Lognormal::Lognormal() {
	mu = 0;
	sigma = 0.1;
}

Lognormal::Lognormal(const RandomVariable::vector_type& v) {
	if (v.size() != 2) {
		throw std::invalid_argument("Lognormal object can only be created with a size 2 vector");
	}
	mu = v[0];
	try {
		setSigma(v[1]);
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl;
	}
}

Lognormal::Lognormal(const Statistics& s) {
	mu = log(s.mean / (sqrt(1 + pow(s.std, 2) / pow(s.mean, 2))));
	try {
		setSigma(squareRoot(log(1 + pow(s.std, 2) / pow(s.mean, 2))));
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl;
	}
}

Lognormal::Lognormal(const double iMu, const double iSig) {
	mu = iMu;
	try {
		setSigma(iSig);
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl;
	}
}

Lognormal::~Lognormal(){}

//    *----------------------------* 
//    |    GETTERS AND SETTERS     |
//    *----------------------------*

void Lognormal::setSigma(const double sval) {
	if (sval <= 0) {
		throw std::invalid_argument("Sigma parameter of Lognormal distribution cannot be zero or below");
	}
	sigma = sval;
}

//    *----------------------------* 
//    |        CALCULATIONS        |
//    *----------------------------*

double Lognormal::mean() const {
	return exp(mu + pow(sigma, 2) / 2); 
}

double Lognormal::median() const {
	return exp(mu); 
}

double Lognormal::mode() const {
	return exp(mu - pow(sigma, 2));
}

// Usuallly we assume variance is > 0, but in the scenario, y = e^x could be negative
double Lognormal::std() const {
	try {
		return squareRoot(variance());
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl;
	}
	return -1;
}

double Lognormal::variance() const {
	return (exp(pow(sigma, 2)) - 1) * exp(2 * mu + pow(sigma, 2));
}

double Lognormal::pdf(const double x) const {
	if (x <= 0) {
		throw std::invalid_argument("Lognormal::pdf() cannot accept an input <= 0");
	}
	return  exp(-pow((log(x) - mu), 2) / (2 * variance())) / (x * sigma * sqrt(2 * M_PI)); 
}

double Lognormal::cdf(const double x) const {
	if (x <= 0) {
		throw std::invalid_argument("Lognormal::cdf() cannot accept an input <= 0");
	}
	return .5 +  .5 * std::erf((log(x) - mu) / (sigma * sqrt(2)));
}

double Lognormal::icdf(double y) const {
    if (y < 0 || y > 1) {
    	throw std::invalid_argument("The probability parameter for Icdf() must be larger than 0 and smaller than 1");
	} else if (isDoubleEqual(y, 0.0)) {
		y = DBL_MIN;
		std::cerr << "icdf(0) will return -Inf; instead DBL_MIN(a value of 1E-37 or smaller) is passed instead" << std::endl;
	} else if (isDoubleEqual(y, 1.0)) {
		y = 1 - DBL_MIN;
		std::cerr << "icdf(1) will return Inf; instead 1 - DBL_MIN(DBL_MIN is 1E-37 or smaller) is passed instead" << std::endl;
	}
	Normal n;
	return exp(n.calcNormInv(y) * sigma + mu);
}

RandomVariable::vector_type Lognormal::getParams() const {
	return {mu, sigma};
}

RandomVariable::vector_type Lognormal::sample(const unsigned int n) const {
	vector_type samples(n);
	std::random_device rd;
	// random number generator
    std::mt19937 gen(rd());
	std::lognormal_distribution<double> dis(mu, sigma);
	// populate samples vector_type by seeding the distribution and generating a sample
	// [&] signals the lambda we are passing by address so the gen object should refer
	// to the previously created object
	std::generate(samples.begin(), samples.end(), [&](){ return dis(gen); });
	return samples;
}
