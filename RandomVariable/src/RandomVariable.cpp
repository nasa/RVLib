/** RandomVariable Object - Implementation
 *	
 *	@file 		(Abstract) Random Variable Class
 *    
 *	@brief 		Random Variable Class - An abstract class outlining the functionality for distributions with
 *				pure virtual functions and aliases to represent data with uncertainty
 *  @note		Virtual functions that are used in late binding must have a definition.
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 29, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <cmath>
#include <stdexcept>
#include <climits>

#include "RandomVariable.h"

Statistics RandomVariable::stats() const {
	return Statistics{ mean(), mode(), std() };
}

double RandomVariable::variance() const { 
	const double sd = std();
	return sd * sd; 
}

double squareRoot(const double x) {
	if (x < 0) {
		throw std::invalid_argument("Square root cannot be taken of a negative.");
	}
	return sqrt(x);
}

bool isDoubleEqual(const double a, const double b) {
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(a - b) < std::numeric_limits<double>::epsilon() * 2;
}
 RandomVariable::~RandomVariable(){}
