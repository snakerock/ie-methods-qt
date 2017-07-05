#ifndef IETYPES_H
#define IETYPES_H

#include <functional>
#include <complex>

using Complex = std::complex<double>;

template <typename value_t>
using fx_t = std::function<value_t (double)>;

template <typename value_t>
using fxy_t = std::function<value_t (double, double)>;

#endif // IETYPES_H
