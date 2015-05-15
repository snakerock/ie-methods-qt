#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <functional>
#include <complex>
#include <cmath>

#include "approximation.h"
#include "iterationmethodpositive.h"
#include "ietypes.h"

void test_e_ixy()
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
