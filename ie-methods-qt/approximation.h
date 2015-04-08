#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <functional>
#include <exception>
#include <vector>
#include <cmath>
#include <map>
#include <array>

#include "complex.h"
#include "ietypes.h"

// Grid function approximation
class Approximation
{
private:
    // Grid function values [x, y] = [key, value]
    std::map<Complex, Complex> grid;

    // Pointer to exact function if present
    c_fx_ptr exactFunction;

    // False by default
    bool isGridFunction;

public:
    // Create empty approximation of grid function, fill by addXY
    Approximation();

    // Wrap exact function to Approximation
    Approximation(c_fx_ptr &func);

    // Create grid function approximation by existing values
    Approximation(std::map<Complex, Complex> &gridFunction);

    // Add [x, y] as [key, value] to grid
    void addXY(const Complex x, const Complex y);

    // Get approximated function value by x
    Complex F(const Complex x);

    // Use Approximation as functor, calls F(x)
    Complex operator()(const Complex x);

    /*
    Approximation operator+ (Approximation a);
    Approximation operator- (Approximation a);
    Approximation operator* (Approximation a);
    Approximation operator/ (Approximation a);
    */
};

#endif // APPROXIMATION_H
