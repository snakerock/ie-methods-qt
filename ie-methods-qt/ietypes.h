#ifndef IETYPES_H
#define IETYPES_H

#include <functional>
#include <complex>

typedef std::complex<double> Complex;

template <typename T>
using fx_t = std::function<T (double)>;

template <typename T>
using fxy_t = std::function<T (double, double)>;

#endif // IETYPES_H
