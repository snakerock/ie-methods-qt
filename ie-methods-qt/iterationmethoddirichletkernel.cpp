#include "iterationmethoddirichletkernel.h"


double IterationMethodDirichletKernel::K(double x, double y) const
{
    double arg = this->k * (y - x);
    if (arg != 0.0) {
        return std::sin(this->b * arg) / arg;
    } else {
        return 1.0;
    }
}

IterationMethodDirichletKernel::IterationMethodDirichletKernel(
        fx_t<Complex> rightPart,
        double parameterK,
        double upperBound,
        int partsNumber
        ) :
    IterationMethodPositive<double>(0.0, upperBound, partsNumber),
    k (parameterK)
{
    // Modified right part function F(x) = (integral from 0 to stepb) (cos(kxt) * Re(f(t)) + sin(kxt) * Im(f(t))) * dt
    this->fPointer = [this, rightPart] (double x) {
        fx_t<double> integrand = [this, x, rightPart] (double t) {
            Complex ft = rightPart(t);
            return std::cos(this->k * x * t) * ft.real() + std::sin(this->k * x * t) * ft.imag();
        };

        return this->integrate(integrand);
    };
}

double IterationMethodDirichletKernel::getParameterK() const
{
    return k;
}
