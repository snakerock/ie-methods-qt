
#include "mathfunctions.h"
#include <math.h>


double MathFunctions::Kernels::e_abs_x_y(double x, double y)
{
    return exp(-fabs(x - y));
}


double MathFunctions::RightParts::f_kernel_e_abs_x_y(double y)
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
