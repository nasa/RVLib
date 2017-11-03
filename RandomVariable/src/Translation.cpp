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

#include <iostream>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>

#include "Translation.h"

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
// |     	  SAMPLING            |
// *------------------------------*

template<typename T>
T Translation::sampleMC(const RandomVariableContainer* rvc, const unsigned int n) {
	std::vector<double> args(rvc->getSize());
	std::vector<double> samples;
	std::vector<RandomVariable*> rvs = rvc->getData();
	// This is for efficiency if n is large
	std::vector<RandomVariable*>::const_iterator cit;
	unsigned int j;
	for (unsigned int i = 0; i < n; i++) {
		for (cit = rvs.cbegin(), j = 0; cit != rvs.cend(); cit++, j++) {
			args[j] = (*cit)->sampleSingle();
		}
		samples.push_back(rvc->equation(args));
	}
	return T(samples);
}

// Based on math found in http://statweb.stanford.edu/~owen/mc/Ch-var-adv.pdf
template<typename T>
T Translation::sampleLH(const RandomVariableContainer* rvc, const unsigned int nSam) {
	const unsigned int nVar = rvc->getSize();
	std::vector<double> samples;
	std::vector< std::vector<double> > U(nVar);
	std::vector< std::vector<double> > X(nVar);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0,1);

	// First, populate randomly - standard uniform [0,1]
	for (unsigned int i = 0; i < nVar; i++) {
		for (unsigned int j = 0; j < nSam; j++) {
			U[i].push_back(dis(gen));
		}
	}

	// and then variable by variable to re-arrange
	for (unsigned int i = 0; i < nVar; i++) {
		std::vector<int> nSampleVec(nSam);
		std::iota(nSampleVec.begin(), nSampleVec.end(), 0); // fill with 0, 1, 2...
		std::random_shuffle(nSampleVec.begin(), nSampleVec.end());
		for (unsigned int j = 0; j < nSam; j++) {
			X[i].push_back((nSampleVec[j] + U[i][j]) / nSam);
		}
	}

	std::vector<double> args(nVar);
	for (unsigned int j = 0; j < nSam; j++) {
		for (unsigned int i = 0; i < nVar; i++) {
			args[i] = rvc->getData()[i]->sampleSingleIcdf(X[i][j]);
		}
		samples.push_back(rvc->equation(args));
	}
	return T(samples);
}

// *------------------------------* 
// |    EXPLICIT INSTANTIATION    |
// *------------------------------*

template Weighted Translation::sample<Weighted>(const Parametric*, const unsigned int);
template Unweighted Translation::sample<Unweighted>(const Parametric*, const unsigned int);

template Normal Translation::fit<Normal>(const NonParametric*);
template Lognormal Translation::fit<Lognormal>(const NonParametric*);

template Unweighted Translation::sampleMC<Unweighted>(const RandomVariableContainer*, const unsigned int);
template Weighted Translation::sampleMC<Weighted>(const RandomVariableContainer*, const unsigned int);

template Unweighted Translation::sampleLH<Unweighted>(const RandomVariableContainer*, const unsigned int);
template Weighted Translation::sampleLH<Weighted>(const RandomVariableContainer*, const unsigned int);
