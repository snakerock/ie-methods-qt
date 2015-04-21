#ifndef ITERATIONMETHODDIRICHLETKERNEL_H
#define ITERATIONMETHODDIRICHLETKERNEL_H

#include "mathextensions.h"
#include "ietypes.h"
#include "iterationmethodpositive.h"

class IterationMethodDirichletKernel : public IterationMethodPositive
{
protected:
    /*
     * MATHS PARAMETERS
     *
     * Consider equation:
     *
     * (integral from 0 to b) e^(ikxy) * u(y) * dy = f(x),
     *
     * where k is positive parameter,
     * f(x) is complex function
     */

    // Parameter k > 0
    double k;

    /*
     * METHOD PARAMETERS
     *
     * Consider iterative method:
     *
     *                       (F(x) - (integral from 0 to b) K(x,y) * u[n-1](y) * dy)
     * u[n](x) = u[n-1](x) + -------------------------------------------------------,
     *                                                 D(x)
     * K(x, y) = sin(k * b * (y - x) / (k * (y - x),
     * D(x) = (integral from 0 to b) K(x,y) * dy,
     * F(x) = (integral from 0 to b) (cos(kxt) * Re(f(t)) + sin(kxt) * Im(f(t))) * dt,
     * u[0](x) = 0;
     */

    // Kernel function K(x, y) = sin(k * b * (y - x) / (k * (y - x)
    virtual double K(double x, double y) const override;

public:
    IterationMethodDirichletKernel(
            complex_fx_t rightPart,
            double parameterK = 1.0,
            double upperBound = 1.0,
            double step = 1e-3
            );

    double getParameterK() const;
};

#endif // ITERATIONMETHODDIRICHLETKERNEL_H
