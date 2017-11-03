// A simple example with samples

#include "Unweighted.h"
#include "Weighted.h"
#include "Translation.h"

int main() {
    // Create samples
    Unweighted samples({1.0, 2.3, 4.4});
    
    printf("We've created a set of %zu unweighted samples: {", samples.getSize());
    for (auto & sample : samples.getData()) {
        printf("%f,", sample);
    }
    printf("\b}\n");
    
    // Add a sample
    samples.append(5.5);
    printf("Now there are %zu unweighted samples: {", samples.getSize());
    for (auto & sample : samples.getData()) {
        printf("%f,", sample);
    }
    printf("\b}\n");
    
    // Change one
    samples.set(2, 2.5);
    printf("We've changed the third one to 2.5: {");
    for (auto & sample : samples.getData()) {
        printf("%f,", sample);
    }
    printf("\b}\n");
    
    // Print
    printf("You can also print this way:\n");
    samples.printData();
    
    // Properties
    printf("Here are some properties of the samples:\n");
    printf("\t Mean:%f\n", samples.mean());
    printf("\t Standard Deviation:%f\n", samples.std());
    printf("\t Variance:%f\n\n", samples.variance());
    
    // Graph - Not exciting
    printf("\n\n You can graph them too:\n");
    samples.graph();
    
    // Set it so there are some duplicates
    printf("\n\n Heres a more interesting one:\n");

    samples.append(2.3);
    samples.append(2.5);
    samples.graph();

    // Convert to weighted
    printf("\nHere's the sampe distribution as weighted samples\n");
    Weighted wSamples(samples.getWData());
    samples.graph();
}
