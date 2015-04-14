#include "iterationmethodpositive.h"

IterationMethodPositive::IterationMethodPositive(
        c_fx_ptr rightPart,
        c_fxy_ptr kernel,
        double lowerBound,
        double upperBound,
        double step
        ) :
    f (rightPart),
    K (kernel),
    a (lowerBound),
    b (upperBound),
    dx (step)
{
    Reinitialize();
}

IterationMethodPositive::~IterationMethodPositive()
{
}

void IterationMethodPositive::Reinitialize()
{
    c_fx_ptr zero = [] (double) { return Complex(); };
    curU = Approximation(zero);
}

Complex IterationMethodPositive::integrate(Approximation app) const
{
    Complex result = 0;

    for (double x = a + dx * 0.5; x < b; x += dx){
        result += app(x);
    }
    result *= dx;

    return result;
}

c_fx_ptr IterationMethodPositive::Iterate(int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation();
        for (double x = a + dx * 0.5; x < b; x += dx) {

            c_fx_ptr Kx = [this, x] (double y) { return K(x, y); };
            Complex D = integrate(Kx);

            c_fx_ptr Kux = [this, x] (double y) { return K(x, y) * prevU(y); };
            Complex IKux = integrate(Kux);

            curU.addXY(x, prevU(x) + (f(x) - IKux) / D);
        }
    }

    return curU;
}

c_fx_ptr IterationMethodPositive::GetCurrentApproximation() const
{
    return curU;
}
