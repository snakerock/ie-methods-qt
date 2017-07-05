#ifndef ITERATIONMETHODHANKEL_H
#define ITERATIONMETHODHANKEL_H

#include <boost/math/special_functions/hankel.hpp>

#include "mathextensions.h"
#include "ietypes.h"
#include "iterationmethodpositive.h"

class IterationMethodHankel : public IterationMethodPositive<Complex>
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
    double k;
    double dh;

    virtual Complex K(double x, double y) const override;

    Complex CalculateSumUI(Approximation<Complex> u, double x);

public:

    IterationMethodHankel(
            fx_t<Complex> rightPart,
            double parameterK = 1.0,
            double upperBound = 1.0,
            int partsNumber = 1e+3,
            int hPartsNumber = 1,
            fx_t<Complex> solution = nullptr
            );

    virtual fx_t<Complex> Iterate (int n = 1) override;

    double getParameterK() const;
};

#endif // ITERATIONMETHODHANKEL_H
