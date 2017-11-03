#include <iostream>
#include <cmath>

#include "Normal.h"
#include "Unweighted.h"
#include "Lognormal.h"
#include "Translation.h"

double step(double x) {
	return x*x;
}

double foo() {
	return 5;
}

double cal(const std::vector<double>& factors) {
	if (factors.size() != 3) {
		throw "cal() must be given three factors";
	}
	return factors[0] + factors[1] + factors[2];
}

NonParametric* sampleDistParams(Parametric* p) {
	return new Unweighted(Translation::sample<Unweighted>(p, 125));
}

void printParams(RandomVariable * rv) {
	std::cout << rv->mean() << std::endl;
	std::cout << rv->std() << std::endl;
}

int main(){
#if 0
	// TEST #1
	/**	@brief		Testing the creation of a basic normal distribution and sampling from a 
	 *				Parametric distribution to a NonParametric distribution 
	 */
	//==============================================================================================
	Parametric* pExample = new Normal(5, .5);
	Unweighted pnExample = Translation::sample<Unweighted>(pExample, 1000);
	pnExample.printData();
	//==============================================================================================

	// TEST #2
	/**	@brief		Testing accessor methods set and get, then examining contents */		
	//==============================================================================================
	for (unsigned int i = 0; i < 1000; i++) {
		// Replace with indexing, it's more natural
		pnExample.set(i, step(pnExample.get(i)));
	}
	pnExample.printData();
	//==============================================================================================

	// TEST #3
	/**	@brief		Testing mean and standard deviation methods	
	 *	@details	Functions that don't start with get can contain calculations,
	 *				in the case of a Normal distribution, the mu and sigma attributes
	 *				happen to correspond to mean and standard deviation, but this
	 *				usually is not the case
	 */
	//==============================================================================================
	std::cout << pnExample->mean() << std::endl;
	std::cout << pnExample->std() << std::endl;
	//==============================================================================================

	// TEST #4
	/**	@brief		Testing implicit copy constructor of Normal(and Parametric)
	 *				distribution
	 */
	//==============================================================================================
	Normal* pExample_1 = new Normal(*pExample); // or RandomVariable* pExample_1 = new Normal(*pExample);
	//==============================================================================================

	// TEST #5
	/**	@brief		Testing function for accessing parameters	*/
	//==============================================================================================
	std::vector<double> params = pExample->getParams();
	for (std::vector<double>::iterator it = params.begin(); it != params.end(); it++) {
		std::cout << *it << std::endl;
	}
	//==============================================================================================

	// TEST #6
	/**	@brief		Creating a NonParametric pointer pointing to a dynamically
	 *				allocated Unweighted object, then appending values to the data set
	 */
	//==============================================================================================
	NonParametric* fooExample = new Unweighted();
	for (unsigned int i = 0; i < 100; i++) {
		fooExample->append(foo());
	}
	fooExample->printData();
	//==============================================================================================

	// TEST #7
	/**	@brief		Appending values to an Unweighted object, fitting to a Normal distribution
	 *				then calculating tenth percentile and pdf/cdf of the value of foo()	
	 */
	//==============================================================================================
	for (unsigned int i = 1; i < 100; i++) {
		fooExample->append(foo()); // changed foo call for testing purposes
		std::cout << "mean: " << fooExample->mean() << std::endl;
		std::cout << "variance: " << fooExample->variance() << std::endl;
	}
	Parametric* n = new Normal(Translation:fit<Normal>(fooExample));
	double num = foo();
	std::cout << "Tenth percentile: "<< norm->icdf(0.1) << std::endl;
	std::cout << "Cumulative probability of " << num << ": " << norm->cdf(num) << std::endl;
	std::cout << "Probability of " << num << ": " << norm->pdf(num) << std::endl;

	// TEST #8
	/**	@brief		Testing getter function on NonParametric distribution object	*/
	//==============================================================================================
	std::cout << fooExample->get(99) << std::endl; 

	// TEST #9
	/**	@brief		Fitting an unweighted object to lognormal and normal distributions
	 *				then comparing the fits via rSquared
	 */
	//==============================================================================================
	Parametric* norm = new Normal(Translation::fit<Normal>(fooExample));
	Parametric* logExample = new Lognormal(Translation::fit<Lognormal>(fooExample));
	double lnormFit = Translation::rSquared(logExample, fooExample); 
	double normFit = Translation::rSquared(norm, fooExample); 
	std::cout << lnormFit << std::endl;
	std::cout << normFit << std::endl;

	// TEST #10
	/**	@brief		Create and call a function that takes a RandomVariable 
	 *				and prints its parameters
	 */
	//==============================================================================================
	RandomVariable* rv = new Normal(0,1);
	printParams(rv);

	// TEST #11
	/**	@brief		Testing a function that creates a NonParametric object instantiated by 
	 *				sampling a Parametric distribution
	 */
	//==============================================================================================
	Parametric* p = new Normal(0,1);
	NonParametric* uw = sampleDistParams(p);
	uw->printData();

	// TEST #12
	/**	@brief		Testing sampling a RandomVariableContainer object	
	 *	@details	Instantiate a normal, lognormal, and unweighted distribution then create a 
	 *				RandomVariable pointer vector and pass to the RandomVariableContainer and sample
	 */
	//==============================================================================================
	NonParametric* uws = new Unweighted();
	NonParametric* luws = new Unweighted();
	for (unsigned int i = 0; i < 100; i++) {
		uws->append(i);
		luws->append(i*2);
	}

	RandomVariable* g = new Normal(0, 1);
	RandomVariable* l = new Lognormal(Translation::fit<Lognormal>(luws));

	std::vector<RandomVariable*> rvs;
	rvs.push_back(g);
	rvs.push_back(l);
	rvs.push_back(uws);
	
	RandomVariableContainer* rvc = new RandomVariableContainer(cal, rvs);
	Weighted w = Translation::sampleMC<Weighted>(rvc, 100);
	w.graph(2);
#endif
	return 0;
}
