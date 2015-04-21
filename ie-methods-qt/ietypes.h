#ifndef IETYPES_H
#define IETYPES_H

#include <functional>
#include <complex>

using Complex = std::complex<double>;
using complex_fx_t = std::function<Complex (double)>;
using fx_t = std::function<double (double)>;
using fxy_t = std::function<double (double, double)>;

#endif // IETYPES_H
