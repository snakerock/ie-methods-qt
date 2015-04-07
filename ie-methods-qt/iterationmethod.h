#ifndef ITERATIONMETHOD_H
#define ITERATIONMETHOD_H

#include <functional>
#include <vector>

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
    double step;

    // u[n], current approximation
    std::vector<double> curU;

    // u[n-1]
    std::vector<double> prevU;

public:
    IterationMethod (
            std::function<double (double)> rightPart,
            std::function<double (double, double)> kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0
            );

    void Reinitialize ();
    std::function<double> Iterate (int n = 1);
    std::function<double> GetCurrentApproximation ();
};

#endif // ITERATIONMETHOD_H
