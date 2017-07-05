#include "iterationmethodpositive.h"


template <typename value_t>
IterationMethodPositive<value_t>::IterationMethodPositive (
        fx_t<value_t> rightPart,
        fxy_t<value_t> kernel,
        double lowerBound,
        double upperBound,
        int partsNumber,
        fx_t<value_t> solution
        ) :
    fPointer (rightPart),
    kernelPointer (kernel),
    a (lowerBound),
    b (upperBound),
    partsNumber (partsNumber),
    dx ((b - a) / (double) partsNumber),
    iterationNumber(0)
{
    if (rightPart == nullptr) {
        fPointer = [this, solution] (double y) {
                fx_t<value_t> sk = [this, y, solution] (double x) { return solution(x) * this->K(x, y); };
                return this->integrate(sk);
            };
    }
    Reinitialize();
}

template <typename value_t>
IterationMethodPositive<value_t>::IterationMethodPositive(
        double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    a (lowerBound),
    b (upperBound),
    partsNumber (partsNumber),
    dx ((b - a) / (double) partsNumber),
    iterationNumber(0)
{
    Reinitialize();
}

template <typename value_t>
IterationMethodPositive<value_t>::~IterationMethodPositive()
{ }

template <typename value_t>
void IterationMethodPositive<value_t>::Reinitialize ()
{
    fx_t<value_t> zero = [] (double) { return 0.0; };
    curU = Approximation<value_t>(zero);
    iterationNumber = 0;
}

template <typename value_t>
fx_t<value_t> IterationMethodPositive<value_t>::Iterate (int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation<value_t>();
        for (double x = a + dx * 0.5; x < b; x += dx) {

            fx_t<value_t> Kx = [this, x] (double y) { return K(x, y); };
            value_t D = integrate(Kx);

            fx_t<value_t> Kux = [this, x] (double y) { return K(x, y) * prevU(y); };
            value_t IKux = integrate(Kux);

            curU.addXY(x, prevU(x) + (f(x) - IKux) / D);
        }
        iterationNumber++;
    }

    return curU;
}

template <typename value_t>
fx_t<value_t> IterationMethodPositive<value_t>::GetCurrentApproximation () const
{
    return curU;
}

template <typename value_t>
fx_t<value_t> IterationMethodPositive<value_t>::GetPreviousApproximation () const
{
    return prevU;
}


template <typename value_t>
value_t IterationMethodPositive<value_t>::f(double x) const
{
    return fPointer(x);
}

template <typename value_t>
value_t IterationMethodPositive<value_t>::K(double x, double y) const
{
    return kernelPointer(x, y);
}

template <typename value_t>
value_t IterationMethodPositive<value_t>::integrate(Approximation<value_t> app) const
{
    return integrate(app, a, b, dx);
}

template <typename value_t>
value_t IterationMethodPositive<value_t>::integrate(Approximation<value_t> app, double from, double to, double delta) const
{
    value_t result = 0;

    for (double x = from + delta * 0.5; x < to; x += delta) {
        result += app(x);
    }
    result *= delta;

    return result;
}

template <typename value_t>
double IterationMethodPositive<value_t>::getDifference(fx_t<value_t> a, fx_t<value_t> b)
{
    if (a == nullptr || b == nullptr) {
        return 0.0;
    }

    double d = 0;
    for (double x = this->dx * 0.5; x <= 1.0; x += this->dx) {
        double t = std::fabs(a(x) - b(x));
        d += t * t;
    }
    return std::sqrt(d);
}

template <typename value_t>
int IterationMethodPositive<value_t>::getIterationNumber() const
{
    return iterationNumber;
}

template <typename value_t>
fx_t<value_t> IterationMethodPositive<value_t>::getFPointer() const
{
    return fPointer;
}

template <typename value_t>
fxy_t<value_t> IterationMethodPositive<value_t>::getKernelPointer() const
{
    return kernelPointer;
}

template <typename value_t>
double IterationMethodPositive<value_t>::getB() const
{
    return b;
}

template <typename value_t>
double IterationMethodPositive<value_t>::getA() const
{
    return a;
}

template <typename value_t>
int IterationMethodPositive<value_t>::getPartsNumber() const
{
    return partsNumber;
}

template <typename value_t>
double IterationMethodPositive<value_t>::getDx() const
{
    return dx;
}

template class IterationMethodPositive<double>;
template class IterationMethodPositive<Complex>;
