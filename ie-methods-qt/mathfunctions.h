#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "ietypes.h"


namespace MathFunctions
{
    namespace Kernels
    {
        double e_abs_x_y(double x, double y);
    }


    namespace RightParts
    {
        double f_kernel_e_abs_x_y_exp(double x);
        double f_kernel_e_abs_x_y_cos_pi(double x);
        double f_kernel_e_abs_x_y_sin_2pi(double x);

        Complex f_dirichlet_exp(double y);
        Complex f_dirichlet_ident(double y);
    }


    namespace Solutions
    {
        double exponent(double y);
        double identical(double y);
        double cosinus_pi(double y);
        double sinus_2pi(double y);
    }
}


#endif // MATHFUNCTIONS_H
