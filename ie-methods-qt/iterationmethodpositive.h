#ifndef ITERATIONMETHODPOSITIVE_H
#define ITERATIONMETHODPOSITIVE_H

#include <functional>
#include <vector>
#include <limits>

#include "ietypes.h"
#include "approximation.h"

template <typename value_t>
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
    fx_t<value_t> fPointer;

    // Right part function for concrete right part inherited methods
    virtual value_t f(double x) const;

    // Kernel function pointer
    fxy_t<value_t> kernelPointer;

    // Kernel function for concrete kernel inherited methods
    virtual value_t K(double x, double y) const;

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

    int iterationNumber;

    // u[n], current approximation
    Approximation<value_t> curU;

    // u[n-1]
    Approximation<value_t> prevU;

    // Rectangle integration from a to b
    value_t integrate(const Approximation<value_t> app) const;
    value_t integrate(const Approximation<value_t> app, double from, double to, double delta) const;

    IterationMethodPositive (
            double lowerBound = 0.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3
            );

public:

    IterationMethodPositive (
            fx_t<value_t> rightPart,
            fxy_t<value_t> kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3,
            fx_t<value_t> solution = nullptr
            );

    virtual ~IterationMethodPositive();

    // Clean current computed approximations, set u[0] = 0
    virtual void Reinitialize ();

    // Iterate n steps next, preserving computed state between calls
    virtual fx_t<value_t> Iterate (int n = 1);

    // Get curU as function pointer
    virtual fx_t<value_t> GetCurrentApproximation () const;

    // Get prevU as function pointer
    virtual fx_t<value_t> GetPreviousApproximation () const;

    // Get Euclid norm || a(x) - b(x) ||
    double getDifference(const fx_t<value_t> a, const fx_t<value_t> b);

    int getIterationNumber() const;

    fx_t<value_t> getFPointer() const;

    fxy_t<value_t> getKernelPointer() const;

    double getA() const;
    double getB() const;
    double getDx() const;
    int getPartsNumber() const;
};

#endif // ITERATIONMETHODPOSITIVE_H
