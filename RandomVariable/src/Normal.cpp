/** Normal Object - Implementation
 *	
 *	@file 		Normal Distribution Class
 *    
 *	@brief 		Normal Distribution Class - Class used for storing and accessing a normal(gaussian) distribution
 * 				representing data with uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 29, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <random>
#include <cfloat> // DBL_MIN

#include "Normal.h"

//    *-------------------------------------* 
//    |    CONSTRUCTORS AND DESTRUCTORS     |
//    *-------------------------------------*

Normal::Normal() {
	mu = 0;
	sigma = 0.1;
}

Normal::Normal(const Statistics& s) {
	mu = s.mean;
	// s.std could negative or zero
	try {
		setSigma(s.std);
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl;
	}
}

Normal::Normal(const RandomVariable::vector_type& v) {
	if (v.size() != 2) {
		throw std::invalid_argument("Normal object can only be created with a size 2 vector");
	}
	mu = v[0];
	try {
		setSigma(v[1]);
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl; 
	}
}

Normal::Normal(const double iMu, const double iSig) {
	mu = iMu;
	try {
		setSigma(iSig);
	} catch (std::invalid_argument& iva) {
		std::cerr << iva.what() << std::endl;
	}
}

Normal::~Normal(){}

//    *----------------------------* 
//    |    GETTERS AND SETTERS     |
//    *----------------------------*

void Normal::setSigma(const double sval) {
	if (sval <= 0) {
		throw std::invalid_argument("Sigma parameter for a Normal distribution cannot be negative or zero");
	}
	sigma = sval;
}

RandomVariable::vector_type Normal::getParams() const {
	return {mu, sigma};
}

//    *----------------------------* 
//    |        CALCULATIONS	 	   |
//    *----------------------------*

double Normal::pdf(const double x) const {
	return exp(-pow(x - mu, 2) / (2 * variance())) / sqrt(2 * M_PI * variance()); 
}

double Normal::cdf(const double x) const {
	return .5 +  .5 * std::erf((x - mu) / (sigma * sqrt(2)));
}

double Normal::icdf(double y) const {
    if (y < 0 || y > 1) {
    	throw std::invalid_argument("The probality parameter for Icdf() must be larger than 0 and smaller than 1");
    } else if (isDoubleEqual(y, 0.0)) {
		y = DBL_MIN;
		std::cerr << "icdf(0) will return -Inf; instead DBL_MIN(a value of 1E-37 or smaller) is passed instead" << std::endl;
	} else if (isDoubleEqual(y, 1.0)) {
		y = 1 - DBL_MIN;
		std::cerr << "icdf(1) will return Inf; instead 1 - DBL_MIN(DBL_MIN is 1E-37 or smaller) is passed instead" << std::endl;
	}
	return calcNormInv(y) * sigma + mu;
}

double Normal::calcNormInv(const double p) const {
    double q, r, val;
    q = p - 0.5;
    /*-------------- use AS 241 ---------------- */
    /**	double ppnd16_(double *p, long *ifault)
	 *      ALGORITHM AS241  APPL. STATIST. (1988) VOL. 37, NO. 3
	 *	Produces the normal deviate Z corresponding to a given lower
     *	tail area of P; Z is accurate to about 1 part in 10**16.
     */
    if (fabs(q) <= .425) {/* 0.075 <= p <= 0.925 */
    	r = .180625 - q * q;
    	val = q * (((((((r * 2509.0809287301226727 + 33430.575583588128105) * r + 67265.770927008700853) * r + 45921.953931549871457) * r + 13731.693765509461125) * r + 1971.5909503065514427) * r + 133.14166789178437745) * r + 3.387132872796366608)
    	/ (((((((r * 5226.495278852854561 + 28729.085735721942674) * r + 39307.89580009271061) * r + 21213.794301586595867) * r + 5394.1960214247511077) * r + 687.1870074920579083) * r + 42.313330701600911252) * r + 1);
    } else { /* closer than 0.075 from {0,1} boundary */
    	/* r = min(p, 1-p) < 0.075 */
   		if (q > 0) {
    		r = 1 - p;
    	} else {
    		r = p;
		}

		try {
    		r = squareRoot(-log(r));
		} catch (std::invalid_argument& iva) {
			std::cerr << iva.what() << std::endl;
		}
    	/* r = squareRoot(-log(r))  <==>  min(p, 1-p) = exp( - r^2 ) */
    	
    	if (r <= 5) { /* <==> min(p,1-p) >= exp(-25) ~= 1.3888e-11 */
    		r += -1.6;
    		val = (((((((r * 7.7454501427834140764e-4 + .0227238449892691845833) * r + .24178072517745061177) * r + 1.27045825245236838258) * r + 3.64784832476320460504) * r + 5.7694972214606914055) * r + 4.6303378461565452959) * r + 1.42343711074968357734)
    		/ (((((((r * 1.05075007164441684324e-9 + 5.475938084995344946e-4) * r + .0151986665636164571966) * r + .14810397642748007459) * r + .68976733498510000455) * r + 1.6763848301838038494) * r + 2.05319162663775882187) * r + 1);
    	} else { /* very close to  0 or 1 */
    		r += -5;
    		val = (((((((r * 2.01033439929228813265e-7 + 2.71155556874348757815e-5) * r + .0012426609473880784386) * r + .026532189526576123093) * r + .29656057182850489123) * r + 1.7848265399172913358) * r + 5.4637849111641143699) * r + 6.6579046435011037772)
   			/ (((((((r * 2.04426310338993978564e-15 + 1.4215117583164458887e-7) * r + 1.8463183175100546818e-5) * r + 7.868691311456132591e-4) * r + .0148753612908506148525) * r + .13692988092273580531) * r + .59983220655588793769) * r + 1);
    	}
   		if (q < 0.0) {
    		val = -val;
    	}
    }
    return val;
}

RandomVariable::vector_type Normal::sample(const unsigned int n) const {
	vector_type samples(n);
	std::random_device rd;
	// random number generator
    std::mt19937 gen(rd());
	std::normal_distribution<double> dis(mu, sigma);
	// populate samples vector_type by seeding the distribution and generating a sample
	// [&] signals the lambda we are passing by address so the gen object should refer
	// to the previously created object
	std::generate(samples.begin(), samples.end(), [&](){ return dis(gen); });
	return samples;
}
