#include "iterationmethodnegative.h"

IterationMethodNegative::IterationMethodNegative(
        c_fx_ptr rightPart,
        c_fxy_ptr kernel,
        Complex lowerBound,
        Complex upperBound,
        Complex step
        ) :
    IterationMethodPositive(rightPart, kernel, lowerBound, upperBound, step)
{ }

c_fx_ptr IterationMethodNegative::Iterate(int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation();
        for (Complex x = a + dx * 0.5; x < b; x += dx) {

            c_fxy_ptr L = [this] (Complex x, Complex y) {
                c_fx_ptr Lt = [this, x, y] (Complex t) {
                    return (this->K(t, x) * this->K(t, y)).Conjugate();
                };

                return this->integrate(Lt);
            };

            c_fx_ptr Lx = [this, x, L] (Complex y) { return L(x, y); };
            Complex D = integrate(Lx);

            c_fx_ptr Lux = [this, x, L] (Complex y) { return L(x, y) * prevU(y); };
            Complex IKux = integrate(Lux);

            c_fx_ptr F = [this] (Complex x) {
                c_fx_ptr Kft = [this, x] (Complex t) {
                    return (this->K(t, x) * this->f(t)).Conjugate();
                };

                return integrate(Kft);
            };

            curU.addXY(x, prevU(x) + (F(x) - IKux) / D);
        }
    }

    return curU;
}
