#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <functional>
#include <exception>
#include <vector>
#include <cmath>
#include <tuple>
#include <map>
#include <array>

// Grid function approximation
class Approximation
{
private:
    std::map<double, double> grid;
    std::function<double (double)> exactFunction;

    bool isGridFunction;

    double distance(double a, double b);

public:
    Approximation();
    Approximation(std::function<double (double)> &func);
    Approximation(std::map<double, double> &gridFunction);

    void addXY(double x, double y);
    double F(double);
    double operator()(double arguments);
    /*
    Approximation operator+ (Approximation a);
    Approximation operator- (Approximation a);
    Approximation operator* (Approximation a);
    Approximation operator/ (Approximation a);
    */
};

#endif // APPROXIMATION_H
