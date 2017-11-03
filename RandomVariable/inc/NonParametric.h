/** NonParametric Object - Header
 *	
 *	@file 		(Abstract) Non-Parametic Distribution Class
 *    
 *	@brief 		NonParametric Distribution Class - Skeleton class declarations for a nonparametric distribution class representing 
 *				value uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		June 28, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#ifndef RV_NONPARAMETRIC_H
#define RV_NONPARAMETRIC_H

#include "RandomVariable.h"

class NonParametric: public RandomVariable {
public:
	// *------------------------------* 
	// |   CONSTRUCTOR/DESTRUCTORS    |
	// *------------------------------*

	/**	@brief	NonParametric destructor if destructor is called on a RandomVariable pointer */
	virtual ~NonParametric();

	// *------------------------------* 
	// |     	  ACCESSORS           |
	// *------------------------------*

	/** @brief		Appends a double value to the member data set
	 *
	 *	@param	d	Any real number
	 */
	virtual void append(const double d) = 0;

	/** @brief		Retrieves value in the kth position from the data set 
	 *
	 *	@param	k	Position of target value
	 *	@returns 	Desired double value from set
	 */
	virtual double get(const size_type k) const = 0;
	
	/** @brief		Returns data represented as an unweighted sample set
	 *
	 *	@returns 	std::vector<double> of data set values
	 */
	virtual vector_type getData() const = 0;

	/** @brief		Returns data represented as an weighted sample set
	 *
	 *	@returns 	std::vector< f_pair > of data set values and their frequencies
	 */
	virtual pvector_type getWData() const = 0;

	// *------------------------------* 
	// |         CALCULATIONS         |
	// *------------------------------*

	/** @brief		Calculates mean value frequency within data set
	 *
	 *	@returns 	Mean frequency value (always > 0 if set size > 0)
	 *	@example	NonParametric* p = new Unweighted({1, 2, 3, 4, 5, 6});
	 *				p->meanHeight() // 1
	 *	@example	NonParametric* p = new Unweighted({1, 1, 3, 4, 5, 5});
	 *				p->meanHeight() // 1.5
	 */
	virtual double meanHeight() const = 0;

	// *------------------------------* 
	// |            VISUAL            |
	// *------------------------------*
    
    /** @brief		Visual representation of value frequencies
     */
    void graph();
    
    /** @brief		Visual representation of value frequencies on intervals of length uInterval
     *
     *	@param	uInterval	Unsigned int representing interval length
     */
    void graph(const unsigned int uInterval);

	/** @brief		Prints data set for testing */
	virtual void printData() const = 0;
};

#endif //RV_NONPARAMETRIC_H
