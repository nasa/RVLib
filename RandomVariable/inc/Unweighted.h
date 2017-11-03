/** Unweighted Object - Header
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

#ifndef RV_NPAR_UNWEIGHTED_H
#define RV_NPAR_UNWEIGHTED_H

#include "NonParametric.h"

class Unweighted: public NonParametric{
public: 
	// *------------------------------* 
	// |   CONSTRUCTORS/DESTRUCTORS   |
	// *------------------------------*

	/** @brief		Value constructor taking in a vector of doubles 
	 *
	 *	@remark		Explicit keyword forbids a vector_type object from being implicitly cast
	 *	@param	v	A vector of doubles
	 */
	explicit Unweighted(const vector_type& v);

	/** @brief		Value constructor taking in a vector of value - frequency pairs 
	 *
	 *	@remark		Explicit keyword forbids a pvector_type object from being implicitly cast
	 *	@param	pv	A vector of pairs (std::pair<double, unsigned int>)
	 */
	explicit Unweighted(const pvector_type&);

	/**	@brief	Unweighted destructor if destructor is called on a RandomVariable pointer */
	~Unweighted();

	// *------------------------------* 
	// |          ACCESSORS           |
	// *------------------------------*

	/** @brief		Retrieves number of values in a data set	
	 *
	 *	@returns	number of values in data set	
	 */
	inline size_type getSize() const {
		return data.size();
	}

	/** @brief		Returns data represented as a vector of pairs (std::pair<double, unsigned int>)
	 *
	 *	@returns 	The data set as a vector of pairs (std::pair<double, unsigned int>)
	 */
	pvector_type getWData() const;

	/** @brief		Returns data represented as a vector of doubles
	 *
	 *	@returns 	The data set as a vector of double
	 */
	inline vector_type getData() const {
		return data;
	}

	/** @brief		Retrieves value in the kth position from the data set 
	 *
	 *	@param	k	Zero-indexed position of target value
	 *	@returns 	Desired double value from set
	 *
	 *	@throws		std::invalid_argument exception
	 *	@example	Unweighted uw({ 1, 2, 3, 5, 2, 4, 5, 6 });
	 *				uw.get(5) == 4; // True
	 */
	double get(const size_type k) const;

	/** @brief		Assigns value in the kth position to f_pair 
	 *
	 *	@param	k	Zero-indexed position of target value
	 *	@param	d	value to be assigned
	 *
	 *	@throws		std::invalid_argument exception
	 *	@example	Unweighted uw({ 1, 2, 3, 5, 2, 4, 5, 6 });
	 *				uw.set(5, 3); // uw == {1, 2, 3, 5, 2, 3, 5, 6}
	 */
	void set(const size_type k, const double d);

	/** @brief		Appends a value to the data set	
	 *
	 *	@param	d	double value in set to be appended
	 */
	void append(const double d);

	// *------------------------------* 
	// |         CALCULATIONS         |
	// *------------------------------*

	/** @brief		Calculates mean of the data set
	 *
	 *	@returns 	Calculated mean 
	 */
	double mean() const;

	/** @brief		Calculates median of the data set
	 *
	 *	@returns 	Calculated median 
	 */
	double median() const;

	/** @brief		Calculates standard deviation of the data set
	 *
	 *	@returns 	Calculated standard deviation
	 */
    double std() const;

	/** @brief		Calculates most frequent value of dataset
	 *
	 *	@returns 	Calculated mode
	 */
    double mode() const;

	/** @brief		Calculates mean value frequency within data set
	 *
	 *	@returns 	mean frequency value (always > 0 if set size > 0)
	 *	@example	Unweighted uw({1, 2, 3, 4, 5, 6});
	 *				uw.meanHeight() // 1
	 *	@example	Unweighted uw({1, 1, 3, 4, 5, 5});
	 *				uw.meanHeight() // 1.5
	 */
	double meanHeight() const;

	// *------------------------------* 
	// |          SAMPLING            |
	// *------------------------------*

	/** @brief 		Sample a single value from a data set
	 *
	 *	@returns	A single double sample value
	 */
	double sampleSingle() const;

	/** @brief 		Sample of multiple values from a data set
	 *
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample values
	 */
	vector_type sample(const unsigned int n) const;

	/** @brief 		Currently identical for sampleSingle()
	 *	@details	This function is different for Parametric distributions and in 
	 *				Translation we are calling it with late binding on a RandomVariable
	 *				pointer that could be pointing to an Unweighted object 
	 *
	 * 	@param	y	Throwaway value
	 *	@pre		y must be a real number in [0,1]
	 *	@returns 	A std::vector<double> of sample values
	 */
	double sampleSingleIcdf(const double y) const;

	/** @brief 		Currently identical for sample()
	 *	@details	This function is different for Parametric distributions and in 
	 *				Translation we are calling it with late binding on a RandomVariable
	 *				pointer that could be pointing to an Unweighted object 
	 *
	 *	@param 	v	throwaway value
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample output values
	 */
	vector_type sampleIcdf(const unsigned int n, const vector_type& v) const;

	// *------------------------------* 
	// |           VISUAL             |
	// *------------------------------*

	/** @brief		Prints data set for testing purposes */
	void printData() const;

private:

	/** @brief		Return iterator pointing to the first object of the data structure	*/
	inline vtype_iterator begin() {
		return data.begin();
	}

	/** @brief		Return iterator pointing to the last object of the data structure	*/
	inline vtype_iterator end() {
		return data.end();
	}

	/** @brief		Return const iterator pointing to the first object of the data structure	*/
	inline const_vtype_iterator cbegin() const {
		return data.cbegin();
	}

	/** @brief		Return const iterator pointing to the last object of the data structure	*/
	inline const_vtype_iterator cend() const {
		return data.cend();
	}

	vector_type data;
};
#endif //RV_NPAR_UNWEIGHTED_H
