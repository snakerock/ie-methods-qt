#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

#include "ietypes.h"

class Complex
{
public:
    double re;
    double im;

    Complex (double re = 0.0,
             double im = 0.0);

    double SqAbs () const;
    double Abs () const;

    Complex Conjugate() const;

    explicit operator double ();

    Complex operator + (const Complex c) const;
    Complex operator - (const Complex c) const;
    Complex operator * (const Complex c) const;
    Complex operator / (const Complex c) const;

    Complex operator += (const Complex c);
    Complex operator -= (const Complex c);
    Complex operator *= (const Complex c);
    Complex operator /= (const Complex c);

    bool operator > (const Complex c) const;
    bool operator < (const Complex c) const;
    bool operator >= (const Complex c) const;
    bool operator <= (const Complex c) const;
    bool operator == (const Complex c) const;

    static c_fx_ptr RealFunctionWrap(r_fx_ptr realFunction) {
        return [realFunction] (Complex x) -> Complex { return (double) realFunction((double) x); };
    }

    static c_fxy_ptr RealFunctionWrap(r_fxy_ptr realFunction) {
        return [realFunction] (Complex x, Complex y) -> Complex { return (double) realFunction((double) x, (double) y); };
    }

    friend std::ostream &operator << (std::ostream &out, const Complex c);
    friend std::istream &operator >> (std::istream &in, Complex c);
};

#endif // COMPLEX_H
