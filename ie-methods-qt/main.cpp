#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <functional>
#include <cmath>
#include "approximation.h"
#include "iterationmethod.h"

double ex(double x, double y)
{
    return exp(fabs(x - y));
}

double f(double y)
{
    if (y <= 0) {
        return (exp(1.0) - 1.0) * exp(-y);
    }
    if (y > 0 && y < 1) {
        return exp(1.0 - y) + exp(y) - 2.0;
    }
    if (y >= 1) {
        return (exp(1.0) - 1.0) * exp(y - 1.0);
    }
}

int main(int argc, char *argv[])
{
    IterationMethod im(f, ex);
    std::function<double(double)> u = im.Iterate(100);

    for (double x = 0.0; x <= 1.0; x+= 10e-3) {
        std::cout << "u(" << x << ") = " << u(x) << std::endl;
    }
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
