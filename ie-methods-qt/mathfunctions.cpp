
#include "mathfunctions.h"
#include <math.h>


double MathFunctions::Kernels::e_abs_x_y(double x, double y)
{
    return exp(-fabs(x - y));
}


double MathFunctions::RightParts::f_kernel_e_abs_x_y_exp(double y)
{
    if (y <= 0) {
        return exp(y);
    }
    if (y > 0 && y < 1) {
        return sinh(y) - exp(y) * (y - 1.0);
    }
    if (y >= 1) {
        return 0.5 * (exp(2.0) - 1.0) * exp(-y);
    }
}


double MathFunctions::Solutions::exponent(double y)
{
    return exp(y);
}


double MathFunctions::Solutions::identical(double y)
{
    return y;
}


Complex MathFunctions::RightParts::f_dirichlet_exp(double y)
{
    return -Complex(0.0, 1.0) * (-1.0 + std::exp(1.0 + Complex(0.0, 1.0) * y)) / (y - Complex(0.0, 1.0));
}


Complex MathFunctions::RightParts::f_dirichlet_ident(double y)
{
    return (-1.0 + std::exp(Complex(0.0, 1.0) * y) * (1.0 - Complex(0.0, 1.0) * y)) / (y * y);
}



double MathFunctions::Solutions::cosinus_pi(double y)
{
    return std::cos(M_PI*y);
}



double MathFunctions::RightParts::f_kernel_e_abs_x_y_cos_pi(double x)
{
    double e = exp(1);
    double I1 = exp(x) - e*M_PI*sin(M_PI*x) + e*cos(M_PI*x);
    I1 /= e + M_PI * M_PI * e;

    double I2 = -exp(-x) + M_PI*sin(M_PI*x) + cos(M_PI*x);
    I2 /= 1 + M_PI*M_PI;

    return I1 + I2;
}



double MathFunctions::Solutions::sinus_2pi(double y)
{
    return std::sin(2*M_PI*y);
}



double MathFunctions::RightParts::f_kernel_e_abs_x_y_sin_2pi(double x)
{
    double e = exp(1);
    double I1 = -2*M_PI*exp(x) + e*sin(2*M_PI*x) + 2*e*M_PI*cos(2*M_PI*x);
    I1 /= e + 4 * M_PI * M_PI * e;

    double I2 = 2*M_PI*exp(-x) + sin(2*M_PI*x) - 2*(M_PI)*cos(2*M_PI*x);
    I2 /= 1 + 4*M_PI*M_PI;

    return I1 + I2;
}
