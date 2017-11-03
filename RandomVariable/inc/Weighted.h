/** Weighted Object - Header
 *	
 *	@file 		Weighted Sample Class
 *    
 *	@brief 		Weighted Sample Class - Class used for storing and accessing a vector of 
 * 				values(double) and their frequencies(unsigned int) representing data with uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		July 25, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#ifndef RV_NPAR_WEIGHTED_H
#define RV_NPAR_WEIGHTED_H

#include <stdexcept>

#include "NonParametric.h"

class Weighted: public NonParametric {
public: 
	// *------------------------------* 
	// |   CONSTRUCTORS/DESTRUCTORS   |
	// *------------------------------*

	/**	@brief		Default constructor that initializes size to 0 */
	Weighted();

	/** @brief		Value constructor taking in a vector of doubles 
	 *
	 *	@remark		Explicit keyword forbids a vector_type object from being implicitly cast
	 *	@remark		Not const because input vector is sorted	
	 *	@param	v	A vector of doubles
	 */
	explicit Weighted(vector_type v);

	/** @brief		Value constructor taking in a vector of value - frequency pairs 
	 *
	 *	@remark		Explicit keyword forbids a pvector_type object from being implicitly cast
	 *	@param	pv	A vector of pairs (std::pair<double, unsigned int>)
	 */
	explicit Weighted(const pvector_type& pv);

	/**	@brief	Weighted destructor if destructor is called on a RandomVariable pointer */
	~Weighted();

	// *------------------------------* 
	// |           ACCESSORS          |
	// *------------------------------*

	/** @brief		Retrieves number of values in a data set	
	 *
	 *	@returns	number of values in data set	
	 */
	inline size_type getSize() const {
		return size;
	}

	/** @brief		Retrieves number of value-frequency pairs in data set
	 *
	 *	@remark		This value can be different from getSize()
	 *	@returns	Data set size
	 */
	inline size_type getNumPairs() const {
		return data.size();
	}

	/** @brief		Retrieves frequency of double value in data set or exception if value not in data set
	 *
	 *	@param	d	Target value whose frequency is returned
	 *	@throws		std::invalid_argument exception
	 *	@returns	Frequency of value in data set
	 */
	inline unsigned int getFreq(const double val) const { 			    
		const_ptype_iterator it = findValPtr(val);
		if (it == cend()) {
			throw std::invalid_argument("Value not found in the data set");
		}
		return it->second;
	}

	/** @brief		Returns data represented as a vector of pairs (std::pair<double, unsigned int>)
	 *
	 *	@returns 	The data set as a vector of pairs (std::pair<double, unsigned int>)
	 */
	inline pvector_type getWData() const {
		return data;
	}

	/** @brief		Returns data represented as a vector of doubles
	 *
	 *	@returns 	The data set as a vector of double
	 */
	vector_type getData() const;

	/** @brief		Retrieves pair in the kth position of the data set 
	 *
	 *	@param	k	Zero-indexed position of target value
	 *	@returns 	Desired double value from set
	 *
	 *	@throws		std::out_of_range exception
	 *	@example	Weighted w({ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 });
	 *
	 *				w.getPair(0) == 1; // True
	 *				w.getPair(2); // Throws std::out_of_range exception
	 */
	f_pair getPair(const size_type k) const;

	/** @brief		Retrieves value in the kth position from the data set 
	 *
	 *	@param	k	Zero-indexed position of target value
	 *	@returns 	Desired double value from set
	 *
	 *	@throws		std::invalid_argument exception
	 *	@example	Weighted w({ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 });
	 *				w.get(5) == 2; // True
	 */
	double get(const size_type k) const;

	/** @brief		Assigns value in the kth position to f_pair 
	 *
	 *	@param	k	Zero-indexed position of target value
	 *	@param	p	f_pair object to be assigned
	 *
	 *	@throws		std::invalid_argument exception
	 *	@example	Weighted w({ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 });
	 *				w.set(0, std::make_pair(7,2)); // w == {7, 7, 2, 2, 2, 2, 2}
	 */
	void set(const size_type k, const f_pair p);

	/** @brief		Assigns a frequency unsigned integer to a double value within the data set 
	 *
	 *	@param	k	zero-indexed position of target value
	 *	@param	d	double value in set to assign to
	 *
	 *	@throws		std::invalid_argument exception
	 *	@throws		std::out_of_range exception
	 *	@example	Weighted w({ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 });
	 *				w.set(1, 2); // w == {1, 1, 2, 2, 2, 2, 2}
	 */
	void setFreq(const double d, const size_type k);

	/** @brief		Appends a value-frequency pair to the data set	
	 *
	 *	@param	p	f_pair object to append
	 *
	 *	@remark		If the value already exists in the data set, the frequency will add to that pair
	 *	@example	Weighted w({ 1, 2, 2 });
	 *				w.append(std::make_pair(3,2)); // w == {1, 2, 2, 3, 3}
	 */
	void append(const f_pair p);

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

	/** @brief		Calculates median of the distribution
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
	 *	@remark		Currently just returning one of the modes if there is more than one
	 *	@returns 	Calculated mode
	 */
    double mode() const;

	/** @brief		Calculates mean value frequency within data set
	 *
	 *	@returns 	mean frequency value (always > 0 if set size > 0)
	 *	@example	Weighted w({1, 2, 3, 4, 5, 6});
	 *				w.meanHeight() // 1
	 *	@example	Weighted w({1, 1, 3, 4, 5, 5});
	 *				w.meanHeight() // 1.5
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
	 *				pointer that could be pointing to a Weighted object 
	 *
	 * 	@param	y	Throwaway value
	 *	@pre		y must be a real number in [0,1]
	 *	@returns 	A std::vector<double> of sample values
	 */
	double sampleSingleIcdf(const double y) const;

	/** @brief 		Currently identical for sample()
	 *	@details	This function is different for Parametric distributions and in 
	 *				Translation we are calling it with late binding on a RandomVariable
	 *				pointer that could be pointing to a Weighted object 
	 *
	 *	@param 	v	throwaway value
	 *	@param	n	Number of samples to return within the vector
	 *	@returns 	A std::vector<double> of sample output values
	 */
	vector_type sampleIcdf(const unsigned int n, const vector_type& v) const;

	// *------------------------------* 
	// |           VISUAL             |
	// *------------------------------*

	/** @brief		Prints data set for testing */
	void printData() const;

private:

	/** @brief		Return iterator pointing to the first object of the data structure	
	 *
	 *	@remark		This allows easier swapping of underlying data structure	
	 */
	inline ptype_iterator begin() {
		return data.begin();
	}

	/** @brief		Return iterator pointing to the last object of the data structure	*/
	inline ptype_iterator end() {
		return data.end();
	}

	/** @brief		Return const iterator pointing to the first object of the data structure	*/
	inline const_ptype_iterator cbegin() const {
		return data.cbegin();
	}

	/** @brief		Return const iterator pointing to the last object of the data structure	*/
	inline const_ptype_iterator cend() const {
		return data.cend();
	}
	
	/**	@brief		Set the size of data set (number of pairs within the vector)
	 * 
	 * 	@param	l	New size of data set
	 */
	inline void setSize(const size_type l) {
		size = l;
	}

	/**	@brief		Iterate through the data set and return a const pointer to the target value	
	 * 
	* 	@param	d	Target value being searched for
	 */
	const_ptype_iterator findValPtr(const double d) const;

	/**	@brief		Iterate through the data set and return a pointer to the target value	
	 * 
	 * 	@param	d	Target value being searched for
	 */
	ptype_iterator findValPtr(const double d);

	pvector_type data;
	size_type size;
};
#endif //RV_NPAR_WEIGHTED_H
