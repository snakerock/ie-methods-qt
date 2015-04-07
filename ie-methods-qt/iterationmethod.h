#ifndef ITERATIONMETHOD_H
#define ITERATIONMETHOD_H

#include <functional>
#include <vector>

#include "approximation.h"

class IterationMethod
{
private:
    /*
     * MATHS PARAMETERS
     *
     * Consider equation:
     * (integral from a to b) K(x,y) * u(y) * dy = f(x)
     */

    // Right part
    std::function<double (double)> f;

    // Kernel
    std::function<double (double, double)> K;

    // Lower bound
    double a;

    // Upper bound
    double b;

    /*
     * METHOD PARAMETERS
     *
     * Consider iterative method:
     * u[n](x) = u[n-1](x) + (f(x) - (integral from a to b) K(x,y) * u[n-1](y) * dy) / (integral from a to b) K(x,y) * dy
     * u[0](x) = 0
     */

    // Integration step
    double dx;

    // u[n], current approximation
    Approximation *curU = nullptr;

    // u[n-1]
    Approximation *prevU = nullptr;

    double integrate(Approximation *app);

public:
    IterationMethod (
            std::function<double (double)> rightPart,
            std::function<double (double, double)> kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            double step = 10e-3
            );

    void Reinitialize ();
    std::function<double (double)> Iterate (int n = 1);
    std::function<double (double)> GetCurrentApproximation ();
};

#endif // ITERATIONMETHOD_H
