/** RandomVariable Object - Header
 *	
 *	@file 		(Abstract) Random Variable Class
 *    
 *	@brief 		Random Variable Class - An abstract class outlining the functionality for distributions with
 *				pure virtual functions and aliases to represent data with uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 28, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#ifndef RANDOMVARIABLE_H
#define RANDOMVARIABLE_H

#include <vector>
#include <limits>

/** @struct Statistics
 *	@brief 	An object that allows for easy instantiation of distributions
 */
struct Statistics {
	double mean;
	double mode;
	double std;
};

class RandomVariable {
public:
	// *------------------------------* 
	// |     	   ALIASES            |
	// *------------------------------*

	using size_type = size_t;

	using f_pair = std::pair<double, unsigned int>;

	using pvector_type = std::vector<f_pair>;
	using vector_type = std::vector<double>;

	using ptype_iterator = pvector_type::iterator;
	using vtype_iterator = vector_type::iterator;

	using const_ptype_iterator = pvector_type::const_iterator;
	using const_vtype_iterator = vector_type::const_iterator;

	// *------------------------------* 
	// |   CONSTRUCTOR/DESTRUCTORS    |
	// *------------------------------*

	/**	@brief	RandomVariable destructor if destructor is called on a RandomVariable pointer */
	virtual ~RandomVariable() = 0;

	// *------------------------------* 
	// |     	 CALCULATIONS         |
	// *------------------------------*

	/** @brief		Calculates mean of distribution based on type
	 *
	 *	@returns 	Calculated mean 
	 */
	virtual double mean() const = 0;

	/** @brief		Calculates median of distribution based on type
	 *
	 *	@returns 	Calculated median 
	 */
	virtual double median() const = 0;

	/** @brief		Calculates standard deviation of distribution based on type
	 *
	 *	@returns 	Calculated standard deviation
	 */
    virtual double std() const = 0;

	/** @brief		Calculates most frequent value of distribution or dataset
	 *
	 *	@returns 	Calculated mode
	 */
    virtual double mode() const = 0;

	/** @brief		Calculates variance from either squaring standard deviation 
	 *				or formula associated with the parametric distribution
	 *
	 *	@remark 	variance() is virtual so its subclasses can use the definition 
	 * 				in RandomVariable.cpp or write their own
	 *
	 *	@returns 	Calculated variance 
	 */
	virtual double variance() const;

	/** @brief		Returns a statistics struct containing measurements from a distribution
	 *
	 *	@returns	Statistics object containing distribution information 
	 */
    Statistics stats() const;
 
	// *------------------------------* 
	// |     	   SAMPLING	          |
	// *------------------------------*

	/** @brief 		Sample of distribution not using icdf()
	 *
	 *	@remark		This function is not const because in the curren version one subclass uses
	 *				and increments a static variable
	 *	@returns	A single double sample value
	 */
	virtual double sampleSingle() const = 0;

	/** @brief 		Sample of multiple values from dd`istribution not using icdf()
	 *
	 *	@remark		This function is not const because in the curren version one subclass uses
	 *				and increments a static variable
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample values
	 */
	virtual vector_type sample(const unsigned int n) const = 0;

	/** @brief 		Sample of multiple values from distribution using icdf()
	 *
	 * 	@param	y	Value to be passed to the icdf()
	 *	@pre		y must be a real number in [0,1]
	 *	@returns 	A std::vector<double> of sample values
	 */
	virtual double sampleSingleIcdf(const double y) const = 0;

	/** @brief 		Sample of multiple values from distribution using icdf()
	 *
	 *	@param 	v	vector containing inputs for icdf()
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample output values from icdf()
	 */
	virtual vector_type sampleIcdf(const unsigned int n, const vector_type& v) const = 0;
};

/** @brief		Wrapper to check if input is negative so nan cannot be returned
 *
 *	@param	x	negative or positive value
 *	@throws 	std::invalid_argument exception
 *	@returns 	sqrt() in input	
 */
double squareRoot(const double x);

/** @brief		Checks the equality of float/double values	
 *
 *	@param	a	A double/float value
 *	@param	b	A double/float value
 *	@returns 	Boolean value indicating if both values are equivalent
 */
bool isDoubleEqual(const double a, const double b);

#endif //RANDOMVARIABLE_H
