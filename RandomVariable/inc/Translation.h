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

#include "Parametric.h"
#include "NonParametric.h"

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
}
#endif //RV_TRANSLATION_H
