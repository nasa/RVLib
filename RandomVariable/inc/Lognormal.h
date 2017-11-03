/** Lognormal Object - Header
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

#ifndef RV_PAR_LOGNORMAL_H
#define RV_PAR_LOGNORMAL_H

#include "Parametric.h"

class Lognormal : public Parametric {
public:

	// *------------------------------* 
	// |   CONSTRUCTORS/DESTRUCTORS   |
	// *------------------------------*

	/**	@brief		Default constructor that initializes mu to 0 and sigma to 0.1 
	 *	@post		Sigma cannot be 0 or negative
	 */
	Lognormal();

	/** @brief		Value constructor taking in a Statistics struct
	 *
	 *	@pre		s.std cannot be 0 or negative
	 *	@post		Sigma cannot be 0 or negative
	 *	@remark		Explicit keyword forbids a Statistics object from being implicitly cast
	 *	@remark		Catch statement within function will either catch the invalid_argument 
	 *				exception from squareRoot or setSigma (or neither)
	 *	@param	s	Statistics struct describing a distribution
	 */
	explicit Lognormal(const Statistics& s);

	/** @brief		Value constructor taking in a vector of doubles 
	 *
	 *	@pre		The vector contains two parameters, not datapoints
	 *	@pre		v[1] cannot be 0 or negative
	 *	@post		Sigma cannot be 0 or negative
	 *	@remark		Explicit keyword forbids a vector_type object from being implicitly cast
	 *	@param	v	A vector of doubles (parameters)
	 */
	explicit Lognormal(const vector_type& v);
	
	/** @brief		Value constructor taking in mu and sigma values 
	 *
	 *	@pre		iSigcannot be 0
	 *	@param	iMu		Value to set mu attribute to
	 *	@param	iSig	Value to set sigma attribute to
	 */
	Lognormal(const double iMu, const double iSig);

	/**	@brief	Lognormal destructor if destructor is called on a RandomVariable pointer */
	~Lognormal();

	// *------------------------------* 
	// |           ACCESSORS          |
	// *------------------------------*

	/**	@brief		Set the sigma attribute of the distribution
	 * 
	 *	@pre		sig parameter cannot be 0
	 * 	@param	sig	New sigma value
	 */
	void setSigma(const double sig);

	/**	@brief		Set the mu attribute of the distribution
	 * 
	 * 	@param	mu	New mu value
	 */
	inline void setMu(const double mval) {
		mu = mval;
	}

	/**	@brief		Retrieve the distribution's mu attribute
	 * 
	 * 	@returns	Mu attribute of distribution
	 */
	inline double getMu() const {
		return mu;
	}

	/**	@brief		Retrieve the distribution's sigma attribute
	 * 
	 * 	@returns	Sigma attribute of distribution
	 */
	inline double getSigma() const {
		return sigma;
	}

	/**	@brief		Retrieves the parameters defining the distribution
	 * 
	 * 	@returns	A vector of doubles holding the parameters
	 */
	vector_type getParams() const;

	// *------------------------------* 
	// |     	 CALCULATIONS         |
	// *------------------------------*

	/** @brief		Calculates probability density function for a lognormal distribution
	 *
	 *	@param	x	Input value which subclasses may attach contraints to
	 *	@returns 	Output(y - value) to pdf function
	 */
    double pdf(const double x) const;

	/** @brief		Calculates cumulative density function for a lognormal distribution
	 *
	 *	@remark		Similar to pdf(), but probability is compounded
	 *
	 *	@param	x	Input value to cdf function that can be any real number
	 *	@returns 	Output(y - value) to pdf function
	 */
	double cdf(const double x) const;

	/** @brief		Calculates inverse cumulative density function for a lognormal distribution
	 *
	 *	@remark		Inverts pdf()
	 *	@example	calcIccdf(cdf(x)) = x;
	 *
	 *	@param	y	Input value, since 0 and 1 will return -Inf and Inf respectively a y value of 
	 *				0 is replaced with DBL_MIN(1E-37 or smaller) or 1 - DBL_MIN, respectively 
	 *	@pre		y must be between 0 and 1 inclusive	
	 *	@returns 	Output(y-value) to pdf function
	 */
    double icdf(const double y) const;

	/** @brief		Calculates mean of the distribution
	 *
	 *	@returns 	Calculated mean 
	 */
	double mean() const;

	/** @brief		Calculates median of the distribution
	 *
	 *	@returns 	Calculated median 
	 */
	double median() const;

	/** @brief		Calculates standard deviation of the distribution
	 *
	 *	@returns 	Calculated standard deviation
	 */
    double std() const;

	/** @brief		Calculates most frequent value of the distribution
	 *
	 *	@returns 	Calculated mode
	 */
    double mode() const;

	/** @brief		Calculates standard deviation of the distribution
	 *
	 *	@returns 	Calculated variance 
	 */
	double variance() const;

	// *------------------------------* 
	// |          SAMPLING            |
	// *------------------------------*

	/** @brief 		Sample of multiple values from distribution not using icdf()
	 *
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample values
	 */
	vector_type sample(const unsigned int n) const;

private:
	double mu;
	double sigma;
};
#endif //RV_PAR_LOGNORMAL_H
