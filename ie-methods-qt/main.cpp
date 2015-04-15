#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <functional>
#include <complex>
#include <cmath>

#include "approximation.h"
#include "iterationmethodpositive.h"
#include "iterationmethodcommon.h"
#include "iterationmethoddirichletkernel.h"
#include "ietypes.h"

double kernel_e_abs_x_y(double x, double y)
{
    return exp(-fabs(x - y));
}

double f_kernel_e_abs_x_y(double y)
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

double u_kernel_e_abs_x_y(double y)
{
    return std::exp(y);
}

Complex f_dirichlet(double y)
{
    return -Complex(0.0, 1.0) * (-1.0 + std::exp(1.0 + Complex(0.0, 1.0) * y)) / (y - Complex(0.0, 1.0));
}

double u_dirichlet(double y)
{
    return std::exp(y);
}

Complex f_dirichlet_2(double y)
{
    return (-1.0 + std::exp(Complex(0.0, 1.0) * y) * (1.0 - Complex(0.0, 1.0) * y)) / (y * y);
}

double u_dirichlet_2(double y)
{
    return y;
}

void test_e_abs_x_y()
{
    IterationMethodPositive im(f_kernel_e_abs_x_y, kernel_e_abs_x_y);
    fx_t prevU = im.Iterate();
    fx_t curU = im.Iterate();
    double prevDiff, curDiff, realDiff;
    curDiff = im.getDifference(curU, prevU);

    for (int i = 1; i < 100; ++i) {
        prevDiff = curDiff;
        prevU = curU;
        curU = im.Iterate();

        realDiff = im.getDifference(curU, u_kernel_e_abs_x_y);
        curDiff = im.getDifference(curU, prevU);
        std::cout << "|| u[" << i + 1 << "] - u[" << i << "] || = " << curDiff;
        std::cout << ";\t   || u[" << i + 1 << "] - U || = " << realDiff << std::endl;
        if (curDiff > prevDiff) {
            std::cout << "[WARNING] Divergence" << std::endl;
        }
    }

    for (double x = 10e-3 * 0.5; x <= 1.0; x+= 10e-3) {
        std::cout << "u(" << x << ") = " << curU(x) << std::endl;
    }
}

void test_e_ixy()
{
    IterationMethodDirichletKernel im(f_dirichlet);
    fx_t prevU = im.Iterate();
    fx_t curU = im.Iterate();
    double prevDiff, curDiff, realDiff;
    curDiff = im.getDifference(curU, prevU);

    for (int i = 1; i < 100; ++i) {
        prevDiff = curDiff;
        prevU = curU;
        curU = im.Iterate();

        realDiff = im.getDifference(curU, u_dirichlet);
        curDiff = im.getDifference(curU, prevU);
        std::cout << "|| u[" << i + 1 << "] - u[" << i << "] || = " << curDiff;
        std::cout << ";\t   || u[" << i + 1 << "] - U || = " << realDiff << std::endl;
        if (curDiff > prevDiff) {
            std::cout << "[WARNING] Divergence" << std::endl;
        }
    }

    for (double x = 1e-3 * 0.5; x <= 1.0; x+= 1e-3) {
        std::cout << "u(" << x << ") = " << curU(x) << std::endl;
    }
}

int main(int argc, char *argv[])
{
    //test_e_abs_x_y();
    test_e_ixy();
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
