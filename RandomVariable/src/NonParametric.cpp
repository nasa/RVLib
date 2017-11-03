/** NonParametric Object - Implementation
 *	
 *	@file 		(Abstract) NonParametric Distribution Class
 *    
 *	@brief 		NonParametric Distribution Class - Skeleton class declarations for a non-parametric distribution class representing 
 *				value uncertainty
 * 
 *	@author		Aiden Cullo <aiden.cullo@nasa.gov> 
 *	@date		August 11, 2017 
 * 
 *	@copyright 	Copyright (c) 2013-2017 United States Government as represented by
 *     			the Administrator of the National Aeronautics and Space Administration.
 *     			All Rights Reserved.
 */

#include <iostream>
#include <cmath>
#include <iomanip>

#include "NonParametric.h"

NonParametric::~NonParametric(){}

void NonParametric::graph() {
    RandomVariable::pvector_type tmp = getWData();
    std::sort(tmp.begin(), tmp.end());
    for(auto p : tmp) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2) << p.first << ' ' << std::string(p.second, '*') << '\n';
    }
}

void NonParametric::graph(const unsigned int uInterval) {
    RandomVariable::pvector_type tmp = getWData();
    // Suppressing the -Wsign-conversion flag when adding to integers
    const int sInterval = static_cast<int>(uInterval);
    // sort vector_type of pairs by key
    std::sort(tmp.begin(), tmp.end(), [](const std::pair<double, unsigned int> &left, const std::pair<double, unsigned int> &right) { return left.first < right.first; });
    // starting point for first interval (e.g. n = 10, 15->10)
    int current = (int(floor(tmp.at(0).first)) - int(floor(tmp.at(0).first)) % sInterval) + sInterval;
    const int maxBefore = int(floor(tmp.at(tmp.size() - 1).first)) - int(floor(tmp.at(tmp.size() - 1).first)) % sInterval;
    // number of digits in the last interval lower bound
    const int maxBeforeStr = std::to_string(maxBefore).size();
    // number of digits in the last interval upper bound
    const int maxAfterStr = std::to_string(maxBefore + sInterval).size();
    unsigned int runningSum = 0;
    for(auto p : tmp) {
        if (p.first <= current) {
            runningSum += p.second;
        } else {
            std::cout << std::right << std::setw(maxBeforeStr) << current - sInterval << '-';
            std::cout << std::left << std::setw(maxAfterStr + 1) << current << std::string(runningSum, '*') << '\n';
            current += sInterval;
            runningSum = p.second;
        }
    }
    std::cout << std::right << std::setw(maxBeforeStr) << current - sInterval << '-';
    std::cout << std::left << std::setw(maxAfterStr + 1) << current << std::string(runningSum, '*') << '\n';
}

