#ifndef ITERATIONMETHODPOSITIVE_H
#define ITERATIONMETHODPOSITIVE_H

#include <functional>
#include <vector>

#include "approximation.h"
#include "complex.h"
#include "ietypes.h"

class IterationMethodPositive
{
protected:
    /*
     * MATHS PARAMETERS
     *
     * Consider equation:
     *
     * (integral from a to b) K(x,y) * u(y) * dy = f(x),
     *
     * where K(x, y) is POSITIVE definite kernel
     */

    // Right part
    c_fx_ptr f;

    // Kernel
    c_fxy_ptr K;

    // Lower bound
    double a;

    // Upper bound
    double b;

    /*
     * METHOD PARAMETERS
     *
     * Consider iterative method:
     *
     *                       (f(x) - (integral from a to b) K(x,y) * u[n-1](y) * dy)
     * u[n](x) = u[n-1](x) + -------------------------------------------------------,
     *                                                 D(y)
     * D(y) = (integral from a to b) K(x,y) * dy,
     * u[0](x) = 0;
     */

    // Integration step
    double dx;

    // u[n], current approximation
    Approximation curU;

    // u[n-1]
    Approximation prevU;

    // Rectangle integration from a to b
    Complex integrate(Approximation app) const;

public:
    IterationMethodPositive (
            c_fx_ptr rightPart,
            c_fxy_ptr kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            double step = 10e-3
            );

    ~IterationMethodPositive();

    // Clean current computed approximations, set u[0] = 0
    virtual void Reinitialize ();

    // Iterate n steps next, preserving computed state between calls
    virtual c_fx_ptr Iterate (int n = 1);

    // Get curU as function pointer
    virtual c_fx_ptr GetCurrentApproximation () const;
};

#endif // ITERATIONMETHODPOSITIVE_H
