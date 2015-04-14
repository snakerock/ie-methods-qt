#ifndef ITERATIONMETHODNEGATIVE_H
#define ITERATIONMETHODNEGATIVE_H

#include "iterationmethodpositive.h"
#include "ietypes.h"

template <typename T>
class IterationMethodNegative : public IterationMethodPositive<T>
{
protected:
    /*
     * MATHS PARAMETERS
     *
     * Consider equation:
     *
     * (integral from a to b) K(x,y) * u(y) * dy = f(x),
     *
     * where K(x, y) is NOT POSITIVE definite kernel
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
            fx_t<T> rightPart,
            fxy_t<T> kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            double step = 10e-3
            ) :
        IterationMethodPositive<T>(rightPart, kernel, lowerBound, upperBound, step)
    { }

    // Iterate n steps next, preserving computed state between calls
    virtual fx_t<T> Iterate (int n = 1) override
    {
        for (int m = 0; m < n; ++m) {
            this->prevU = this->curU;

            this->curU = Approximation<T>();
            for (double x = this->a + this->dx * 0.5; x < this->b; x += this->dx) {

                fxy_t<T> L = [this] (double x, double y) {
                    fx_t<T> Lt = [this, x, y] (double t) {
                        return std::conj(this->K(t, x) * this->K(t, y));
                    };

                    return this->integrate(Lt);
                };

                fx_t<T> Lx = [this, x, L] (double y) { return L(x, y); };
                T D = this->integrate(Lx);

                fx_t<T> Lux = [this, x, L] (double y) { return L(x, y) * this->prevU(y); };
                T IKux = this->integrate(Lux);

                fx_t<T> F = [this] (double x) {
                    fx_t<T> Kft = [this, x] (double t) {
                        return std::conj(this->K(t, x) * this->f(t));
                    };

                    return this->integrate(Kft);
                };

                this->curU.addXY(x, this->prevU(x) + (F(x) - IKux) / D);
            }
        }

        return this->curU;
    }

};

#endif // ITERATIONMETHODNEGATIVE_H
