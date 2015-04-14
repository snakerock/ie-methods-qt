#ifndef ITERATIONMETHODPOSITIVE_H
#define ITERATIONMETHODPOSITIVE_H

#include <functional>
#include <vector>

#include "approximation.h"
#include "complex.h"
#include "ietypes.h"

template <typename T>
class IterationMethodPositive
{
protected:
    /*
     * MATHS PARAMETERS
     *
     * Consider equation:
     *
     * (integral from a to b) K(x,y) * u(y) * dy = f(x),
     *
     * where K(x, y) is POSITIVE definite kernel
     */

    // Right part
    fx_t<T> f;

    // Kernel
    fxy_t<T> K;

    // Lower bound
    double a;

    // Upper bound
    double b;

    /*
     * METHOD PARAMETERS
     *
     * Consider iterative method:
     *
     *                       (f(x) - (integral from a to b) K(x,y) * u[n-1](y) * dy)
     * u[n](x) = u[n-1](x) + -------------------------------------------------------,
     *                                                 D(y)
     * D(y) = (integral from a to b) K(x,y) * dy,
     * u[0](x) = 0;
     */

    // Integration step
    double dx;

    // u[n], current approximation
    Approximation<T> curU;

    // u[n-1]
    Approximation<T> prevU;

    // Rectangle integration from a to b
    T integrate(Approximation<T> app) const
    {
        T result = 0;

        for (double x = a + dx * 0.5; x < b; x += dx){
            result += app(x);
        }
        result *= dx;

        return result;
    }

public:
    IterationMethodPositive (
            fx_t<T> rightPart,
            fxy_t<T> kernel,
            double lowerBound = 0.0,
            double upperBound = 1.0,
            double step = 10e-3
            ) :
        f (rightPart),
        K (kernel),
        a (lowerBound),
        b (upperBound),
        dx (step)
    {
        Reinitialize();
    }

    ~IterationMethodPositive()
    { }

    // Clean current computed approximations, set u[0] = 0
    virtual void Reinitialize ()
    {
        fx_t<T> zero = [] (double) { return T(0.0); };
        curU = Approximation<T>(zero);
    }

    // Iterate n steps next, preserving computed state between calls
    virtual fx_t<T> Iterate (int n = 1)
    {
        for (int m = 0; m < n; ++m) {
            prevU = curU;

            curU = Approximation<T>();
            for (double x = a + dx * 0.5; x < b; x += dx) {

                fx_t<T> Kx = [this, x] (double y) { return K(x, y); };
                T D = integrate(Kx);

                fx_t<T> Kux = [this, x] (double y) { return K(x, y) * prevU(y); };
                T IKux = integrate(Kux);

                curU.addXY(x, prevU(x) + (f(x) - IKux) / D);
            }
        }

        return curU;
    }

    // Get curU as function pointer
    virtual fx_t<T> GetCurrentApproximation () const
    {
        return curU;
    }

    static double getDifference(fx_t<T> a, fx_t<T> b)
    {
        double d = 0;
        for (double x = 10e-3 * 0.5; x <= 1.0; x += 10e-3) {
            double t = std::abs(a(x) - b(x));
            d += t * t;
        }
        return sqrt(d);
    }
};

#endif // ITERATIONMETHODPOSITIVE_H
