#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <functional>
#include <exception>
#include <vector>
#include <cmath>
#include <map>
#include <array>

#include "ietypes.h"

// Grid function approximation
template <typename T>
class Approximation
{
private:
    // Grid function values [x, y] = [key, value]
    std::map<double, T> grid;

    // Pointer to exact function if present
    fx_t<T> exactFunction;

    // False by default
    bool isGridFunction;

public:
    // Create empty approximation of grid function, fill by addXY
    Approximation()
        : isGridFunction(true)
    { }

    // Wrap exact function to Approximation
    Approximation(fx_t<T> &func)
        : exactFunction(func), isGridFunction(false)
    { }

    // Create grid function approximation by existing values
    Approximation(std::map<double, T> &gridFunction)
        : grid(gridFunction), isGridFunction(true)
    { }

    // Add [x, y] as [key, value] to grid
    void addXY(const double x, const T y)
    {
        if (isGridFunction) {
            grid[x] = y;
        }
    }

    // Get approximated function value by x
    T F(const double x)
    {
        if (isGridFunction) {
            try {
                return grid.at(x);
            } catch (std::exception e) {
                double nearest;

                for (auto it = grid.begin(); it != grid.end(); it++) {
                    if (it == grid.begin()) {
                        nearest = it->first;
                    } else {
                        if (x < it->first) {
                            break;
                        }
                    }
                }

                return grid.at(nearest);
            }
        } else {
            return exactFunction(x);
        }
    }

    // Use Approximation as functor, calls F(x)
    T operator()(const double x)
    {
        return F(x);
    }

    /*
    Approximation operator+ (Approximation a);
    Approximation operator- (Approximation a);
    Approximation operator* (Approximation a);
    Approximation operator/ (Approximation a);
    */
};

#endif // APPROXIMATION_H
