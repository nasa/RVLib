/** Translation Namespace - Header
 *	
 *	@file 		Translation Namespace
 *    
 *	@brief 		Translation Namespace - Contains functions for translating, comparing,
 * 				fitting, and sampling NonParametric/Parametric distributions
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		July 25, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#ifndef RV_TRANSLATION_H
#define RV_TRANSLATION_H

#include "Normal.h"
#include "Lognormal.h"
#include "Unweighted.h"
#include "Weighted.h"
#include "RandomVariableContainer.h"

namespace Translation {
	// *------------------------------* 
	// |     	TRANSLATION           |
	// *------------------------------*

	/** @brief		Samples a parametric distribution to construct a nonparametric object	
	 *
	 *	@param	p	Pointer to a parametric distribution
	 *	@param	n	Number of samples to generate from the distribution
	 *	@returns 	Instance of S constructed with generated samples 
	 */
	template<typename S>
	S sample(const Parametric* p, const unsigned int n);

	/** @brief		Fits a nonparametric distribution to parametric distribution	
	 *
	 *	@param	np	Pointer to a nonparametric distribution
	 *	@returns 	Instance of D fitted from a nonparametric distribution 
	 */
	template<typename D>
	D fit(const NonParametric* np);

	// *------------------------------* 
	// |     	  SAMPLING            |
	// *------------------------------*

	/** @brief		Generates n samples from multiple parametric distributions using the Monte Carlo method and calls the 
	 *				RandomVariableContainer member function pointer passing in sampled values
	 *
	 *	@param 	n	Number of samples generated
	 *	@param	rvc	Pointer to a RandomVariableContainer object
	 *	@returns 	A NonParametric object (type T) 
	 */
	template<typename T>
	T sampleMC(const RandomVariableContainer* rvc, const unsigned int n);

	/** @brief		Generates n samples from  multiple parametric distributions using the Latin Hypercube method and calls the 
	 *				RandomVariableContainer member function pointer passing in sampled values
	 *
	 *	@param 	n	Number of samples generated
	 *	@param	rvc	Pointer to a RandomVariableContainer object
	 *	@returns 	A NonParametric object (type T) 
	 */
	template<typename T>
	T sampleLH(const RandomVariableContainer* rvc, const unsigned int n);
}
#endif //RV_TRANSLATION_H
