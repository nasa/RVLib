//  Second Example

#include "LogNormal.h"
#include "Unweighted.h"
#include "Translation.h"
#include "Normal.h"

const double MU         = 0;
const double SIGMA      = 0.1;
const int NSamples      = 1000;

int main() {
    // Create an empty LogNormal Distribution
    Lognormal dist;
    
    dist.setMu(MU);
    dist.setSigma(SIGMA);
    
    // get the attributes
    printf("We've now created a lognormal distribution with the parameters mu=%f, sigma=%f\n", dist.getMu(), dist.getSigma());
    printf("This same distribution had the following properties: \n\t Mean: %f\n\t Standard Deviation: %f\n\t Median: %f\n\t Mode: %f\n\t Variance: %f\n", dist.mean(), dist.std(), dist.median(), dist.mode(), dist.variance());
    
    // Sampling
    Unweighted samples(dist.sample(NSamples));
    printf("\n Now we have %d samples with the following properties:\n", NSamples);
    printf("\t Mean:%f\n", samples.mean());
    printf("\t Standard Deviation:%f\n", samples.std());
    printf("\t Variance:%f\n\n", samples.variance());
    
    
    // Fitting - Fit to normal and logNorm, see which is better
    // We are pretending we dont know the distribution type
    auto fitNormal = Translation::fit<Normal>(&samples);
    auto fitLogNorm = Translation::fit<Lognormal>(&samples);
    
    printf("Now we have a normal distribution fit from the samples\n");
    printf("The Mu is %f and the Sigma is %f\n", fitNormal.getMu(), fitNormal.getSigma());
    printf("Now we have a logNormal distribution fit from the samples\n");
    printf("The Mu is %f and the Sigma is %f\n", fitLogNorm.getMu(), fitLogNorm.getSigma());    
}
