#include "iterationmethodnegative.h"

IterationMethodNegative::IterationMethodNegative(
        c_fx_ptr rightPart,
        c_fxy_ptr kernel,
        double lowerBound,
        double upperBound,
        double step
        ) :
    IterationMethodPositive(rightPart, kernel, lowerBound, upperBound, step)
{ }

c_fx_ptr IterationMethodNegative::Iterate(int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation();
        for (double x = a + dx * 0.5; x < b; x += dx) {

            c_fxy_ptr L = [this] (double x, double y) {
                c_fx_ptr Lt = [this, x, y] (double t) {
                    return std::conj(this->K(t, x) * this->K(t, y));
                };

                return this->integrate(Lt);
            };

            c_fx_ptr Lx = [this, x, L] (double y) { return L(x, y); };
            Complex D = integrate(Lx);

            c_fx_ptr Lux = [this, x, L] (double y) { return L(x, y) * prevU(y); };
            Complex IKux = integrate(Lux);

            c_fx_ptr F = [this] (double x) {
                c_fx_ptr Kft = [this, x] (double t) {
                    return std::conj(this->K(t, x) * this->f(t));
                };

                return integrate(Kft);
            };

            curU.addXY(x, prevU(x) + (F(x) - IKux) / D);
        }
    }

    return curU;
}
