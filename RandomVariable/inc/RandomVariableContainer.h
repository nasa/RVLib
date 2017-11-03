/** Random Variable container object - header
 *	
 *	@file 		Random variable container class
 *    
 *	@brief 		Declarations for a random variable container class to hold multiple RandomVariable distribution objects
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		July 7, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#ifndef RV_RANDOMVARIABLECONTAINER_H
#define RV_RANDOMVARIABLECONTAINER_H

#include "RandomVariable.h"

#include <vector>

class RandomVariableContainer {
public:
	// *------------------------------* 
	// |     	   ALIASES            |
	// *------------------------------*

	using f_ptr = double (*)(const RandomVariable::vector_type&);
	
	// *------------------------------* 
	// |   CONSTRUCTORS/DESTRUCTORS   |
	// *------------------------------*

	/**	@brief		Default constructor that initializes eq (member function pointer) to nullptr */
	RandomVariableContainer();

	/** @brief		Value constructor initializing member function pointer and vector of RandomVariable pointers 
	 *
	 *	@pre		The number of RV pointers in rvv and the size of the vector parameter of func have to be the same
	 *	@param	rvv		A vector of RandomVariable pointers
	 *	@param	func	A function taking in a vector as a parameter and returning a double
	 */
	RandomVariableContainer(const f_ptr func, const std::vector<RandomVariable*>& rvv);

	// *------------------------------* 
	// |           ACCESSORS          |
	// *------------------------------*

	/** @brief		Retrieves number of values in the vector of RandomVariable pointers	
	 *
	 *	@returns	Size of RandomVariable pointer vector
	 */
	inline RandomVariable::size_type getSize() const {
		return data.size();
	}
	
	/** @brief		Sets the member function pointer to a function accepting a vector of doubles and returning a double	
	 *
	 *	@param func	A function pointer to a function accepting a vector and returning a double
	 *	@remark		This function must accept a vector that is the same size as the RandomVariable pointer vector
	 */
	void setEquation(const f_ptr func);

	/** @brief		Retrieves the member function pointer to a function accepting a vector of doubles and returning a double	
	 *
	 *	@returns	Member equation	
	 */
	inline f_ptr getEquation() const;

	/** @brief		Adds a RandomVariable pointer to the existing vector	
	 *
	 *	@remark 	Number of RandomVariable pointer cannot exceed the size of the vector parameter to the member function pointer eq
	 *	@param 	rvp	RandomVariable pointer pointing to dynamic memory containing a distribution object	
	 */
	void add(RandomVariable* rvp);

	/** @brief		Returns member vector of RandomVariable pointers
	 *
	 *	@returns 	The vector of RandomVariable pointers
	 */
	inline std::vector<RandomVariable*> getData() const {
		return data;
	}

	/** @brief		Executes member function pointer on input vector
	 *
	 *	@param	v	Vector of doubles to pass to member function pointer
	 *	@returns 	Result of member function pointer being called
	 */
	double equation(const std::vector<double>& v) const;

private:
	std::vector<RandomVariable*> data;
	// function pointer to a function that accepts a vector of doubles and returns a double
	double (*eq)(const std::vector<double>&);
};
#endif //RV_RANDOMVARIABLECONTAINER_H
