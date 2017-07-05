#include "iterationmethodcommon.h"


template <typename value_t>
IterationMethodCommon<value_t>::IterationMethodCommon (double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    IterationMethodPositive<value_t>(lowerBound, upperBound, partsNumber)
{ }

template <typename value_t>
IterationMethodCommon<value_t>::IterationMethodCommon (fx_t<value_t> rightPart,
        fxy_t<value_t> kernel,
        double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    IterationMethodPositive<value_t>(rightPart, kernel, lowerBound, upperBound, partsNumber)
{ }

template <typename value_t>
fx_t<value_t> IterationMethodCommon<value_t>::Iterate (int n)
{
    for (int m = 0; m < n; ++m) {
        this->prevU = this->curU;

        this->curU = Approximation<value_t>();
        for (double x = this->a + this->dx * 0.5; x < this->b; x += this->dx) {

            fxy_t<value_t> L = [this] (double x, double y) {
                fx_t<value_t> Lt = [this, x, y] (double t) {
                    return this->K(t, x) * this->K(t, y);
                };

                return this->integrate(Lt);
            };

            fx_t<value_t> Lx = [this, x, L] (double y) { return L(x, y); };
            value_t D = this->integrate(Lx);

            fx_t<value_t> Lux = [this, x, L] (double y) { return L(x, y) * this->prevU(y); };
            value_t IKux = this->integrate(Lux);

            fx_t<value_t> F = [this] (double x) {
                fx_t<value_t> Kft = [this, x] (double t) {
                    return this->K(t, x) * this->f(t);
                };

                return this->integrate(Kft);
            };

            this->curU.addXY(x, this->prevU(x) + (F(x) - IKux) / D);
        }
        this->iterationNumber++;
    }

    return this->curU;
}
