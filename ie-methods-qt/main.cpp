#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <functional>
#include <complex>
#include <cmath>

#include "approximation.h"
#include "iterationmethodpositive.h"
#include "iterationmethodnegative.h"
#include "ietypes.h"

double ex(double x, double y)
{
    return exp(-fabs(x - y));
}

double fexex(double y)
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

double f1ex(double y)
{
    if (y <= 0.0) {
        return (exp(1.0) - 1.0) * exp(y - 1.0);
    }
    if (y > 0 && y < 1) {
        return -exp(y - 1.0) - exp(-y) + 2.0;
    }
    if (y >= 1) {
        return (exp(1.0) - 1.0) * exp(-y);
    }
}

Complex kernel_e_ixy(double x, double y)
{
    return std::exp(Complex(0.0, 1.0) * x * y);
}

Complex f_e_ixy(double y)
{
    return -Complex(0.0, 1.0) * (-1.0 + std::exp(Complex(0.0, 1.0) * y)) / y;
}

double getDifference(c_fx_ptr a, c_fx_ptr b)
{
    double d = 0;
    for (double x = 10e-3 * 0.5; x <= 1.0; x += 10e-3) {
        double t = std::abs(a(x) - b(x));
        d += t * t;
    }
    return sqrt(d);
}

int main(int argc, char *argv[])
{
    //IterationMethodNegative im(Complex::RealFunctionWrap(fexex), Complex::RealFunctionWrap(ex));
    IterationMethodNegative im(f_e_ixy, kernel_e_ixy);
    c_fx_ptr prevU = im.Iterate();
    c_fx_ptr curU = im.Iterate();
    double prevDiff, curDiff;
    curDiff = getDifference(curU, prevU);

    for (int i = 1; i < 1; ++i) {
        prevDiff = curDiff;
        prevU = curU;
        curU = im.Iterate();

        //curDiff = getDifference(curU, Complex::RealFunctionWrap(exp));
        curDiff = getDifference(curU, prevU);//[] (Complex x) -> Complex { return 1.0; });
        std::cout << "|| u[" << i + 1 << "] - u[" << i << "] || = " << curDiff << std::endl;
        if (curDiff > prevDiff) {
            std::cout << "[WARNING] Divergence" << std::endl;
        }
    }

    for (double x = 10e-3 * 0.5; x <= 1.0; x+= 10e-3) {
        std::cout << "u(" << x << ") = " << curU(x) << std::endl;
    }
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
