#include "complex.h"

#include <cmath>

Complex::Complex (double re,
                  double im) :
    re (re),
    im (im)
{ }

Complex Complex::Conjugate() const
{
    return Complex(re, -im);
}

double Complex::SqAbs () const {
    return re * re + im * im;
}

double Complex::Abs () const {
    return sqrt(SqAbs());
}


Complex Complex::operator + (const Complex c) const
{
    return Complex(re + c.re, im + c.im);
}

Complex Complex::operator - (const Complex c) const
{
    return Complex(re - c.re, im - c.im);
}

Complex Complex::operator * (const Complex c) const
{
    return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
}

Complex Complex::operator / (const Complex c) const
{
    Complex res = *this * c.Conjugate();
    return Complex(res.re / c.Abs(), res.im / c.Abs());
}

Complex Complex::operator += (const Complex c)
{
    *this = *this + c;
    return *this;
}

Complex Complex::operator -= (const Complex c)
{
    *this = *this - c;
    return *this;
}

Complex Complex::operator *= (const Complex c)
{
    *this = *this * c;
    return *this;
}

Complex Complex::operator /= (const Complex c)
{
    *this = *this / c;
    return *this;
}

bool Complex::operator > (const Complex c) const
{
    if (re > c.re) return true;
    if (re < c.re) return false;
    if (im > c.im) return true;
    return false;
}

bool Complex::operator < (const Complex c) const
{
    return c > *this;
}

bool Complex::operator >= (const Complex c) const
{
    return *this > c || *this == c;
}

bool Complex::operator <= (const Complex c) const
{
    return *this < c || *this == c;
}

bool Complex::operator == (const Complex c) const
{
    if (re == c.re && im == c.im) return true;
    return false;
}

Complex::operator double ()
{
    return re;
}

std::ostream &operator << (std::ostream &out, const Complex c)
{
    if (c.re != 0.0 || (c.re == 0.0 && c.im == 0.0)) {
        out << c.re;
    }

    if (c.re != 0.0 && c.im != 0.0) {
        out << "+";
    }

    if (c.im != 0.0) {
        out << c.im << "i";
    }

    return out;
}

std::istream &operator >> (std::istream &in, Complex c)
{
    in >> c.re >> c.im;
    return in;
}
