#include "iterationmethodhankel.h"

Complex IterationMethodHankel::K(double x, double y) const
{
    double kR = k * std::fabs(x - y);
    return Complex(0, 1) / 4.0 * boost::math::cyl_hankel_1(0, kR);
}

Complex IterationMethodHankel::CalculateSumUI(Approximation<Complex> u, double x)
{
    Complex sum = 0.0;
    fx_t<Complex> Gx = [this, x] (double y) { return K(x, y); };
    fx_t<Complex> Jx = [this, x] (double y) {
        double kR = k * std::fabs(x - y);
        return boost::math::cyl_bessel_j(0, kR);
    };

    for (double xn = a + 0.5 * dx; xn < b; xn += dx) {
        if (std::fabs(x - xn) >= 0.001) {
            sum += u(xn) * integrate(Gx, xn - dx * 0.5, xn + dx * 0.5, dh);
        } else {
            Complex I = -1.0 / ( 2.0 * M_PI) * (dx * log(k) - dx + dx * log(dx / 2.0));
            I += Complex(0, 1) / 4.0 * integrate(Jx, xn - dx * 0.5, xn + dx * 0.5, dh);
            sum += u(xn) * I;
        }
    }

    return sum;
}

IterationMethodHankel::IterationMethodHankel(
        fx_t<Complex> rightPart,
        double parameterK,
        double upperBound,
        int partsNumber,
        int hPartsNumber,
        fx_t<Complex> solution
        ) :
    IterationMethodPositive<Complex>(0.0, upperBound, partsNumber),
    k (parameterK)
{
    this->dh = this->dx / hPartsNumber;

    if (rightPart == nullptr) {
        this->fPointer = [this, solution] (double x) { return this->CalculateSumUI(Approximation<Complex>(solution), x); };
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

fx_t<Complex> IterationMethodHankel::Iterate(int n)
{
    for (int m = 0; m < n; ++m) {
        prevU = curU;

        curU = Approximation<Complex>();
        for (double x = a + dx * 0.5; x < b; x += dx) {

            Complex SuI = CalculateSumUI(prevU, x);
            curU.addXY(x, prevU(x) + f(x) - SuI);
        }
        this->iterationNumber++;
    }

    return curU;
}

double IterationMethodHankel::getParameterK() const
{
    return k;
}
