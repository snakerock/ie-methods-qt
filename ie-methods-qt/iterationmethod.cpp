#include "iterationmethod.h"

IterationMethod::IterationMethod(
        std::function<double (double)> rightPart,
        std::function<double (double, double)> kernel,
        double lowerBound,
        double upperBound
        ) :
    f (rightPart),
    K (kernel),
    a (lowerBound),
    b (upperBound)
{
    //Reinitialize();
}
