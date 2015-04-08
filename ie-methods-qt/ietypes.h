#ifndef IETYPES_H
#define IETYPES_H

#include <functional>

class Complex;

typedef std::function<Complex (Complex)> c_fx_ptr;
typedef std::function<Complex (Complex, Complex)> c_fxy_ptr;
typedef std::function<double (double)> r_fx_ptr;
typedef std::function<double (double, double)> r_fxy_ptr;

#endif // IETYPES_H
