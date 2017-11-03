/** Translation Namespace - Implementation
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

#include <vector>

#include "Translation.h"
#include "Normal.h"
#include "LogNormal.h"
#include "UnWeighted.h"
#include "Weighted.h"

// *------------------------------* 
// |     	TRANSLATION           |
// *------------------------------*
template<typename S>
S Translation::sample(const Parametric* p, const unsigned int n) {
	std::vector<double> samples = p->sample(n);
	return S(samples);
}

template<typename D>
D Translation::fit(const NonParametric* samples) {
	return D(samples->stats());
}

// *------------------------------* 
// |    EXPLICIT INSTANTIATION    |
// *------------------------------*

template Weighted Translation::sample<Weighted>(const Parametric*, const unsigned int);
template Unweighted Translation::sample<Unweighted>(const Parametric*, const unsigned int);

template Normal Translation::fit<Normal>(const NonParametric*);
template Lognormal Translation::fit<Lognormal>(const NonParametric*);
