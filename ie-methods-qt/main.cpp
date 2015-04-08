#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <functional>
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

Complex getDifference(c_fx_ptr a, c_fx_ptr b)
{
    Complex d = 0;
    for (Complex x = 10e-3 * 0.5; x <= 1.0; x+= 10e-3) {
        d += (a(x) - b(x)) * (a(x) - b(x));
    }
    return sqrt(d.Abs());
}

int main(int argc, char *argv[])
{
    IterationMethodNegative im(Complex::RealFunctionWrap(fexex), Complex::RealFunctionWrap(ex));
    c_fx_ptr prevU = im.Iterate();
    c_fx_ptr curU = im.Iterate();
    Complex prevDiff, curDiff;
    curDiff = getDifference(curU, prevU);

    for (int i = 1; i < 100; ++i) {
        prevDiff = curDiff;
        prevU = curU;
        curU = im.Iterate();

        curDiff = getDifference(curU, Complex::RealFunctionWrap(exp));
        std::cout << "|| u[" << i + 1 << "] - u[" << i << "] || = " << curDiff << std::endl;
        if (curDiff > prevDiff) {
            std::cout << "[WARNING] Divergence" << std::endl;
        }
    }

    for (Complex x = 10e-3 * 0.5; x <= 1.0; x+= 10e-3) {
        std::cout << "u(" << x << ") = " << curU(x) << std::endl;
    }
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
