#ifndef ITERATIONMETHODDIRICHLETKERNEL_H
#define ITERATIONMETHODDIRICHLETKERNEL_H

#include "ietypes.h"
#include "iterationmethodpositive.h"

class IterationMethodDirichletKernel : public IterationMethodPositive<double>
{
protected:
    double k;

    double dirichletKernel(double x, double y)
    {
        double arg = k * std::abs(x - y);
        return arg != 0.0 ? std::sin(arg) / arg : 1.0;
    }

public:
    IterationMethodDirichletKernel(
            fx_t<double> rightPart,
            double parameterK = 1.0,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            double step = 10e-3
            ) :
        IterationMethodPositive<double>(rightPart, fxy_t<double>(dirichletKernel), lowerBound, upperBound, step),
        k (parameterK)
    { }

    // Iterate n steps next, preserving computed state between calls
    virtual fx_t<double> Iterate (int n = 1) override
    {
        for (int m = 0; m < n; ++m) {
            this->prevU = this->curU;

            this->curU = Approximation<double>();
            for (double x = this->a + this->dx * 0.5; x < this->b; x += this->dx) {

                fx_t<double> Kx = [this, x] (double y) { return this->K(x, y); };
                double D = this->integrate(Kx);

                fx_t<double> Kux = [this, x] (double y) { return this->K(x, y) * this->prevU(y); };
                double IKux = this->integrate(Kux);

                fx_t<double> F = [this] (double x) {
                    fx_t<double> Kft = [this, x] (double t) {
                        return std::cos(-k * x * t) * this->f(t);
                    };

                    return this->integrate(Kft);
                };

                this->curU.addXY(x, this->prevU(x) + (F(x) - IKux) / D);
            }
        }

        return this->curU;
    }

};

#endif // ITERATIONMETHODDIRICHLETKERNEL_H
