#include "iterationmethodpositive.h"


IterationMethodPositive::IterationMethodPositive (
        fx_t rightPart,
        fxy_t kernel,
        double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    fPointer (rightPart),
    kernelPointer (kernel),
    a (lowerBound),
    b (upperBound),
    partsNumber (partsNumber),
    dx ((b - a) / (double) partsNumber)
{
    Reinitialize();
}

IterationMethodPositive::IterationMethodPositive (
        double lowerBound,
        double upperBound,
        int partsNumber
        ) :
    a (lowerBound),
    b (upperBound),
    partsNumber (partsNumber),
    dx ((b - a) / (double) partsNumber)
{
    Reinitialize();
}

IterationMethodPositive::~IterationMethodPositive()
{ }

void IterationMethodPositive::Reinitialize ()
{
    fx_t zero = [] (double) { return 0.0; };
    curU = Approximation(zero);
}

fx_t IterationMethodPositive::Iterate (int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation();
        for (double x = a + dx * 0.5; x < b; x += dx) {

            fx_t Kx = [this, x] (double y) { return K(x, y); };
            double D = integrate(Kx);

            fx_t Kux = [this, x] (double y) { return K(x, y) * prevU(y); };
            double IKux = integrate(Kux);

            curU.addXY(x, prevU(x) + (f(x) - IKux) / D);
        }
    }

    return curU;
}

fx_t IterationMethodPositive::GetCurrentApproximation () const
{
    return curU;
}

fx_t IterationMethodPositive::GetPreviousApproximation () const
{
    return prevU;
}


double IterationMethodPositive::f(double x) const
{
    return fPointer(x);
}

double IterationMethodPositive::K(double x, double y) const
{
    return kernelPointer(x, y);
}

double IterationMethodPositive::integrate(Approximation app) const
{
    double result = 0;

    for (double x = a + dx * 0.5; x < b; x += dx){
        result += app(x);
    }
    result *= dx;

    return result;
}

double IterationMethodPositive::getDifference(fx_t a, fx_t b)
{
    double d = 0;
    for (double x = this->dx * 0.5; x <= 1.0; x += this->dx) {
        double t = std::abs(a(x) - b(x));
        d += t * t;
    }
    return std::sqrt(d);
}

fx_t IterationMethodPositive::getFPointer() const
{
    return fPointer;
}

fxy_t IterationMethodPositive::getKernelPointer() const
{
    return kernelPointer;
}

double IterationMethodPositive::getB() const
{
    return b;
}

double IterationMethodPositive::getA() const
{
    return a;
}

int IterationMethodPositive::getPartsNumber() const
{
    return partsNumber;
}

double IterationMethodPositive::getDx() const
{
    return dx;
}
