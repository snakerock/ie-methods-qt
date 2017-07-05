
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


Complex MathFunctions::RightParts::f_dirichlet_exp(double y, double k, double b)
{
    return -Complex(0.0, 1.0) * (-1.0 + std::exp(b + k * b * Complex(0.0, 1.0) * y)) / (k * y - Complex(0.0, 1.0));
}


Complex MathFunctions::RightParts::f_dirichlet_ident(double y, double k, double b)
{
    return (-1.0 + std::exp(k * b * Complex(0.0, 1.0) * y) * (1.0 - k * b * Complex(0.0, 1.0) * y)) / (k * k * y * y);
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

double MathFunctions::Solutions::one_2pi_ln2_sqrt(double y)
{
    return 1.0 / (2 * M_PI * log(2.0) * sqrt(y * (1.0 - y)));
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


double MathFunctions::Kernels::ln_x_y(double x, double y, double h)
{
    return log(1.0 / sqrt((x - y) * (x - y) + h * h));
}


double MathFunctions::RightParts::f_kernel_ln_x_y_one(double x, double h)
{
    return -0.5 * ((1.0 - x) * (log((1.0 - x) * (1.0 - x) + h * h) - 2.0) + 2.0 * h * atan((1.0 - x) / h) -
                  (-1.0 - x) * (log((-1.0 - x) * (-1.0 - x) + h * h) - 2.0) + 2.0 * h * atan((-1.0 - x) / h));
    return 1.0;
}


double MathFunctions::Solutions::one(double y)
{
    return 1.0;
}

double MathFunctions::Solutions::phi(double y)
{
    //return 1.0;
    return cos(y * M_PI / 3.0);
}


double MathFunctions::Solutions::phi_sqrt(double y, double h)
{
    return phi(y) / sqrt((1.0 - y) * (1.0 + y) + h * h);
}


double MathFunctions::Kernels::ln_abs_x(double x, double y)
{
    return log(1.0 / fabs(x));
}


double MathFunctions::RightParts::f_kernel_ln_abs_x_one(double x)
{
    return -2.0;
}


double MathFunctions::Kernels::ln_abs_x_y(double x, double y)
{
    return log(1.0 / fabs(x-y));
}


double MathFunctions::RightParts::f_kernel_ln_abs_x_y_sqrt(double x)
{
    return -M_PI * log(2.0);
}


double MathFunctions::Solutions::sqrt_1_y2(double y)
{
    return -1.0 / sqrt(1.0 - y * y);
}


Complex MathFunctions::Solutions::complex_cos_plus_sin(double y)
{
    return Complex(cos(y), sin(y));
}


Complex MathFunctions::Kernels::Hankel(double x, double y, double k, double y0)
{
    double kR = k * sqrt((x - y) * (x - y) + y0 * y0);
    return Complex(0, 1) / 4.0 * boost::math::cyl_hankel_1(0, kR);
}


Complex MathFunctions::Solutions::complex_exp(double y)
{
    return Complex(exp(y), 0);
}


double MathFunctions::RightParts::f_kernel_ln_x_y_one_2pi_ln2_sqrt(double x)
{
    return 1.0;
}
