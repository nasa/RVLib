/** RandomVariableContainer - implementation
 *	
 *	@file 		Random Variable Container Class
 *    
 *	@brief 		Random Variable Container Class - Definitions for a random variable container class to hold multiple RandomVariable distribution objects
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		July 7, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <algorithm>

#include "RandomVariableContainer.h"

// *------------------------------* 
// |   CONSTRUCTORS/DESTRUCTORS   |
// *------------------------------*

RandomVariableContainer::RandomVariableContainer() {
	eq = nullptr;
}

RandomVariableContainer::RandomVariableContainer(const f_ptr func, const std::vector<RandomVariable*>& v) {
	data = v;
	setEquation(func);
}

// *------------------------------* 
// |          ACCESSORS           |
// *------------------------------*

void RandomVariableContainer::add(RandomVariable* rv) {
	data.push_back(rv);			
}

void RandomVariableContainer::setEquation(const f_ptr func) {
	if (!func) {
		throw "Equation function not initialized";
	}
	eq = func;
}

// *------------------------------* 
// |        CALCULATIONS          |
// *------------------------------*

double RandomVariableContainer::equation(const std::vector<double>& v) const {
	if (!eq) {
		throw "Equation function not initialized";
	}
	return (*eq)(v);
}
