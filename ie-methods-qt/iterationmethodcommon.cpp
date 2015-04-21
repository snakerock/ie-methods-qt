#include "iterationmethodcommon.h"


IterationMethodCommon::IterationMethodCommon (double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    IterationMethodPositive(lowerBound, upperBound, partsNumber)
{ }

IterationMethodCommon::IterationMethodCommon (fx_t rightPart,
        fxy_t kernel,
        double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    IterationMethodPositive(rightPart, kernel, lowerBound, upperBound, partsNumber)
{ }

fx_t IterationMethodCommon::Iterate (int n)
{
    for (int m = 0; m < n; ++m) {
        this->prevU = this->curU;

        this->curU = Approximation();
        for (double x = this->a + this->dx * 0.5; x < this->b; x += this->dx) {

            fxy_t L = [this] (double x, double y) {
                fx_t Lt = [this, x, y] (double t) {
                    return this->K(t, x) * this->K(t, y);
                };

                return this->integrate(Lt);
            };

            fx_t Lx = [this, x, L] (double y) { return L(x, y); };
            double D = this->integrate(Lx);

            fx_t Lux = [this, x, L] (double y) { return L(x, y) * this->prevU(y); };
            double IKux = this->integrate(Lux);

            fx_t F = [this] (double x) {
                fx_t Kft = [this, x] (double t) {
                    return this->K(t, x) * this->f(t);
                };

                return this->integrate(Kft);
            };

            this->curU.addXY(x, this->prevU(x) + (F(x) - IKux) / D);
        }
    }

    return this->curU;
}
