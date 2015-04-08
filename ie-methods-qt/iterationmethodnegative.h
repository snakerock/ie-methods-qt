#ifndef ITERATIONMETHODNEGATIVE_H
#define ITERATIONMETHODNEGATIVE_H

#include "iterationmethodpositive.h"

class IterationMethodNegative : public IterationMethodPositive
{
protected:
    /*
     * MATHS PARAMETERS
     *
     * Consider equation:
     *
     * (integral from a to b) K(x,y) * u(y) * dy = f(x),
     *
     * where K(x, y) is NEGATIVE definite kernel
     */

    /*
     * METHOD PARAMETERS
     *
     * Consider iterative method:
     *
     *                       (F(x) - (integral from a to b) L(x,y) * u[n-1](y) * dy)
     * u[n](x) = u[n-1](x) + -------------------------------------------------------,
     *                                                 D(y)
     * D(y) = (integral from a to b) L(x,y) * dy,
     * L(x, y) = (integrate from a to b) K*(x, t) * K(t, y) * dt,
     *            _______
     * K*(x, t) = K(t, x),
     * F(x) = (integrate from a to b) K*(x, t) * f(t) * dt
     *
     * u[0](x) = 0
     */

public:
    IterationMethodNegative (
            c_fx_ptr rightPart,
            c_fxy_ptr kernel,
            Complex lowerBound = 0.0,
            Complex upperBound = 1.0,
            Complex step = 10e-3
            );

    // Iterate n steps next, preserving computed state between calls
    virtual c_fx_ptr Iterate (int n = 1) override;
};

#endif // ITERATIONMETHODNEGATIVE_H
