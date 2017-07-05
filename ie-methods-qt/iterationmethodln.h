#ifndef ITERATIONMETHODLN_H
#define ITERATIONMETHODLN_H

#include <boost/math/special_functions/hankel.hpp>

#include "mathextensions.h"
#include "ietypes.h"
#include "iterationmethodpositive.h"

class IterationMethodLn : public IterationMethodPositive<double>
{
    /*
     * METHOD PARAMETERS
     *
     * Consider iterative method:
     *
     *
     * u[n](x[k]) = u[n-1](x[k]) + f(x[k]) -
     *              - (sum from n = 1 to n = N) u[n-1](x[n]) * I(x[n], x[k]),
     *
     *
     * I(x[n], x[k]) = (integral from x[n] - h/2 to x[n] + h/2) G(x[k] - t) * dt, if n != k,
     * I(x[n], x[k]) = h * ln(k) - h + h * ln(h / 2), if n = k,
     * G(R) = i / 4 * H[0, 1](kR),
     * u[0](x) = 0;
     */

protected:

    virtual double K(double x, double y) const override;
    double IK(double x, double from, double to) const;

    double CalculateSumUI(Approximation<double> u, double x);

public:

    IterationMethodLn(
            fx_t<double> rightPart,
            int partsNumber = 1e+3,
            fx_t<double> solution = nullptr
            );

    virtual fx_t<double> Iterate (int n = 1) override;
};

#endif // ITERATIONMETHODLN_H
