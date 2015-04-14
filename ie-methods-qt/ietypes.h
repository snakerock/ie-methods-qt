#ifndef IETYPES_H
#define IETYPES_H

#include <functional>
#include <complex>

typedef std::complex<double> Complex;
typedef std::function<Complex (double)> c_fx_ptr;
typedef std::function<Complex (double, double)> c_fxy_ptr;
typedef std::function<double (double)> r_fx_ptr;
typedef std::function<double (double, double)> r_fxy_ptr;

#endif // IETYPES_H
