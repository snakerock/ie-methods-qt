#include "iterationmethodln.h"

double IterationMethodLn::K(double x, double y) const
{
    double R = std::fabs(x - y);
    return std::log(1.0 / R);
}

double IterationMethodLn::IK(double x, double from, double to) const
{
    fx_t<double> I = [this, x] (double y) {
        double t = y - x;
        return -(t * log(fabs(t)) - t);
    };

    return I(to) - I(from);
}

double IterationMethodLn::CalculateSumUI(Approximation<double> u, double x)
{
    double sum = 0.0;

    for (double xn = a + 0.5 * dx; xn < b; xn += dx) {
        sum += u(xn) * IK(x, xn - dx * 0.5, xn + dx * 0.5);
    }

    return sum;
}

IterationMethodLn::IterationMethodLn(
        fx_t<double> rightPart,
        int partsNumber,
        fx_t<double> solution
        ) :
    IterationMethodPositive<double>(0.0, 1.0, partsNumber)
{
    if (rightPart == nullptr) {
        this->fPointer = [this, solution] (double x) { return this->CalculateSumUI(Approximation<double>(solution), x); };
    } else {
        this->fPointer = rightPart;
    }
}

/*
 * METHOD PARAMETERS
 *
 * Consider iterative method:
 *
 *
 * u[n](x[k]) = u[n-1](x[k]) + f(x[k]) -
 *              - (sum from n = 1 to n = N) u[n-1](x[n]) * I(x[n], x[k]),
 *
 *
 * I(x[n], x[k]) = (integral from x[n] - h/2 to x[n] + h/2) G(x[k] - t) * dt, if n != k,
 * I(x[n], x[k]) = h * ln(k) - h + h * ln(h / 2), if n = k,
 * G(R) = i / 4 * H[0, 1](kR),
 * u[0](x) = 0;
 */

fx_t<double> IterationMethodLn::Iterate(int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation<double>();
        for (double x = a + dx * 0.5; x < b; x += dx) {

            double SuI = CalculateSumUI(prevU, x);
            curU.addXY(x, prevU(x) + f(x) - SuI);
        }
        this->iterationNumber++;
    }

    return curU;
}
