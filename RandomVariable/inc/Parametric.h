/** Parametric Object - Header
 *	
 *	@file 		(Abstract) Parametric Distribution Class
 *    
 *	@brief 		Parametric Distribution Class - Skeleton class declarations for a parametric distribution class representing 
 *				value uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 28, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#ifndef RV_PARAMETRIC_H
#define RV_PARAMETRIC_H

#include "RandomVariable.h"

class Parametric: public RandomVariable {
public: 
	// *------------------------------* 
	// |   CONSTRUCTOR/DESTRUCTORS    |
	// *------------------------------*

	/**	@brief	Parametric destructor if destructor is called on a RandomVariable pointer */
	virtual ~Parametric();

	// *------------------------------* 
	// |     	 CALCULATIONS         |
	// *------------------------------*

	/** @brief		Calculates probability density function for given distribution and input
	 *
	 *	@param	x	Input value which subclasses may attach contraints to
	 *	@returns 	Output(y - value) to pdf function
	 */
    virtual double pdf(const double x) const = 0;

	/** @brief		Calculates cumulative density function for given distribution and input
	 *
	 *	@remark		Similar to pdf(), but probability is compounded
	 *
	 *	@param	x	Input value which subclasses may attach contraints to
	 *	@returns 	Output(y - value) to pdf function
	 */
    virtual double cdf(const double x) const = 0;

	/** @brief		Calculates inverse cumulative density function for given distribution and input
	 *
	 *	@remark		Inverts pdf()
	 *	@example	calcIccdf(cdf(x)) = x;
	 *
	 *	@param	y	Input value, since 0 and 1 will return -Inf and Inf respectively a y value of 
	 *				0 is replaced with DBL_MIN(1E-37 or smaller) or 1 - DBL_MIN, respectively 
	 *	@pre		y must be between 0 and 1 inclusive	
	 *	@returns 	Output(y-value) to pdf function
	 */
    virtual double icdf(const double y) const = 0;

	// *------------------------------* 
	// |     	  ACCESSORS           |
	// *------------------------------*
	
	/** @brief		Returns parameters necessary to define the distribution
	 *
	 *	@returns 	std::vector<double> containing parametrers that define the distribution
	 */
	virtual vector_type getParams() const = 0;

	// *------------------------------* 
	// |     	    SAMPLES           |
	// *------------------------------*
	
	/** @brief 		Sample a single value from a distribution not using icdf()
	 *
	 *	@returns	A single double sample value
	 */
	double sampleSingle() const;

	/** @brief 		Sample of multiple values from distribution using icdf()
	 *
	 * 	@param	P	Value to be passed to the icdf()
	 *	@pre		P must be a real number in [0,1]
	 *	@returns 	A std::vector<double> of sample values
	 */
	double sampleSingleIcdf(const double P) const;
 
	/** @brief 		Sample of multiple values from distribution using icdf()
	 *
	 *	@param 	v	vector containing inputs for icdf()
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample output values from icdf()
	 */
	vector_type sampleIcdf(const unsigned int n, const vector_type& v) const;
};

#endif //RV_PARAMETRIC_H
