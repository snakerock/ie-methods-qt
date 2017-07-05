#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <boost/math/special_functions/hankel.hpp>

#include "ietypes.h"
#include "iterationmethodpositive.h"

namespace MathFunctions
{
    namespace Kernels
    {
        double e_abs_x_y(double x, double y);
        double ln_x_y(double x, double y, double h = 0.1);
        double ln_abs_x(double x, double y);
        double ln_abs_x_y(double x, double y);

        Complex Hankel(double x, double y, double k, double y0);
    }


    namespace RightParts
    {
        double f_kernel_e_abs_x_y_exp(double x);
        double f_kernel_e_abs_x_y_cos_pi(double x);
        double f_kernel_e_abs_x_y_sin_2pi(double x);
        double f_kernel_ln_x_y_one(double x, double h = 0.1);
        double f_kernel_ln_x_y_minus_two(double x);
        double f_kernel_ln_abs_x_one(double x);
        double f_kernel_ln_abs_x_y_sqrt(double x);
        double f_kernel_ln_x_y_one_2pi_ln2_sqrt(double x);

        Complex f_dirichlet_exp(double y, double k = 1.0, double b = 1.0);
        Complex f_dirichlet_ident(double y, double k = 1.0, double b = 1.0);
    }


    namespace Solutions
    {
        double exponent(double y);
        double identical(double y);
        double cosinus_pi(double y);
        double sinus_2pi(double y);
        double one(double y);
        double phi(double y);
        double phi_sqrt(double y, double h = 0.1);
        double sqrt_1_y2(double y);
        double one_2pi_ln2_sqrt(double y);

        Complex complex_cos_plus_sin(double y);
        Complex complex_exp(double y);
    }
}


#endif // MATHFUNCTIONS_H
