#ifndef ITERATIONMETHODPOSITIVE_H
#define ITERATIONMETHODPOSITIVE_H

#include <functional>
#include <vector>

#include "approximation.h"
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

    // Right part pointer
    fx_t fPointer;

    // Right part function for concrete right part inherited methods
    virtual double f(double x) const;

    // Kernel function pointer
    fxy_t kernelPointer;

    // Kernel function for concrete kernel inherited methods
    virtual double K(double x, double y) const;

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
     *                                                 D(x)
     * D(x) = (integral from a to b) K(x,y) * dy,
     * u[0](x) = 0;
     */

    // Partition of [a, b]
    int partsNumber;

    // Integration step
    double dx;

    // u[n], current approximation
    Approximation curU;

    // u[n-1]
    Approximation prevU;

    // Rectangle integration from a to b
    double integrate(Approximation app) const;

    IterationMethodPositive (
            double lowerBound = 0.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3
            );

public:
    IterationMethodPositive (
            fx_t rightPart,
            fxy_t kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3
            );

    ~IterationMethodPositive();

    // Clean current computed approximations, set u[0] = 0
    virtual void Reinitialize ();

    // Iterate n steps next, preserving computed state between calls
    virtual fx_t Iterate (int n = 1);

    // Get curU as function pointer
    virtual fx_t GetCurrentApproximation () const;

    // Get prevU as function pointer
    virtual fx_t GetPreviousApproximation () const;

    // Get Euclid norm || a(x) - b(x) ||
    double getDifference(fx_t a, fx_t b);

    fx_t getFPointer() const;

    fxy_t getKernelPointer() const;

    double getA() const;
    double getB() const;
    double getDx() const;
    int getPartsNumber() const;
};

#endif // ITERATIONMETHODPOSITIVE_H
