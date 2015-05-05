#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <functional>
#include <exception>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>
#include <array>

#include "ietypes.h"

// Grid function approximation
class Approximation
{
private:
    // Grid function values [x, y] = [key, value]
    std::map<double, double> grid;

    // Pointer to exact function if present
    fx_t exactFunction;

    // False by default
    bool isGridFunction;

public:
    // Create empty approximation of grid function, fill by addXY
    Approximation()
        : isGridFunction(true)
    { }

    // Wrap exact function to Approximation
    Approximation(fx_t &func)
        : exactFunction(func), isGridFunction(false)
    { }

    // Create grid function approximation by existing values
    Approximation(std::map<double, double> &gridFunction)
        : grid(gridFunction), isGridFunction(true)
    { }

    // Add [x, y] as [key, value] to grid
    void addXY(const double x, const double y)
    {
        if (isGridFunction) {
            grid[x] = y;
        }
    }

    // Get approximated function value by x
    double F(const double x)
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

                        nearest = it->first;
                    }
                }

                return grid.at(nearest);
            }
        } else {
            return exactFunction(x);
        }
    }

    // Use Approximation as functor, calls F(x)
    double operator()(const double x)
    {
        return F(x);
    }

};

#endif // APPROXIMATION_H
