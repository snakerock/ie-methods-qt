#ifndef ITERATIONMETHODCOMMON_H
#define ITERATIONMETHODCOMMON_H

#include "iterationmethodpositive.h"
#include "ietypes.h"

class IterationMethodCommon : public IterationMethodPositive
{
protected:
    /*
     * Consider equation:
     *
     * (integral from a to b) K(x,y) * u(y) * dy = f(x),
     *
     * where K(x, y) is NOT POSITIVE definite kernel.
     *
     *
     * Consider iterative method:
     *
     *                       (F(x) - (integral from a to b) L(x,y) * u[n-1](y) * dy)
     * u[n](x) = u[n-1](x) + -------------------------------------------------------,
     *                                                 D(x)
     * D(x) = (integral from a to b) L(x,y) * dy,
     * L(x, y) = (integrate from a to b) K*(x, t) * K(t, y) * dt,
     *            _______
     * K*(x, t) = K(t, x),
     * F(x) = (integrate from a to b) K*(x, t) * f(t) * dt
     *
     * u[0](x) = 0
     */

    IterationMethodCommon (
            double lowerBound = 0.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3
            );

public:
    IterationMethodCommon (fx_t rightPart,
            fxy_t kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3
            );

    // Iterate n steps next, preserving computed state between calls
    virtual fx_t Iterate (int n = 1) override;

};

#endif // ITERATIONMETHODCOMMON_H
