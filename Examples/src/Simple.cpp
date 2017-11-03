// A Simple Example

#include "Normal.h"
#include "Translation.h"
#include "Unweighted.h"

const double MEAN   = 5;
const double STDEV  = 0.5;
const int NSamples  = 10;

int main() {
    // Create a Normal Distribution
    Normal dist(MEAN, STDEV);
    
    // Distribution Properties
    printf("Now we have a normal distribution\n");
    printf("The Mean is %f and the Standard Deviation is %f\n", dist.mean(), dist.std());
    printf("Here is the value of the pdf at -1 sigma, mean, and 1 sigma [%f, %f, %f]\n", dist.pdf(MEAN-STDEV), dist.pdf(MEAN), dist.pdf(MEAN+STDEV));
    printf("Here is the values for the cdf [%f, %f, %f]\n", dist.cdf(MEAN-STDEV), dist.cdf(MEAN), dist.cdf(MEAN+STDEV));
    
    // Copying Distribution
    Normal dist2 = dist;
    printf("Here is a copy:\n");
    printf("The Mean is %f and the Standard Deviation is %f\n", dist2.mean(), dist2.std());
    
    
    // Editing Distribution
    dist.setMu(2*MEAN);
    dist.setSigma(1.25*STDEV);
    
    // Sampling
    Unweighted samples(dist.sample(NSamples));
    printf("\n Here are %d samples:\n", NSamples);
    for (auto & sample : samples.getData()) {
        printf("\t%f\n", sample);
    }
    
    // Fitting
    auto fitDist = Translation::fit<Normal>(&samples);
    
    printf("Now we have a normal distribution fit from the samples of the first\n");
    printf("The Mean is %f and the Standard Deviation is %f\n", fitDist.mean(), fitDist.std());
    
    return 0;
}
