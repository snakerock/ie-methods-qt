#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <functional>
#include <exception>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>
#include <array>

#include "types.h"

// Grid function approximation
template <typename value_t>
class Approximation {
public:
    using fx_t = std::function<value_t (double)>;
    using fxy_t = std::function<value_t (double, double)>;
    using map_t = std::map<double, value_t>;

private:
    // Grid function values [x, y] = [key, value]
    map_t grid;

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
    Approximation(fx_t func)
        : exactFunction(func), isGridFunction(false)
    { }

    // Create grid function approximation by existing values
    Approximation(map_t gridFunction)
        : grid(gridFunction), isGridFunction(true)
    { }

    // Add [x, y] as [key, value] to grid
    void addXY(const double x, const value_t y)
    {
        if (isGridFunction) {
            grid[x] = y;
        }
    }

    // Get approximated function value by x
    value_t F(const double x)
    {
        if (isGridFunction) {
            try {
                return grid.at(x);
            } catch (std::exception e) {
                double nearest;
                double delta = 0;

                for (auto it = grid.begin(); it != grid.end(); it++) {
                    if (it == grid.begin()) {
                        nearest = it->first;
                        delta = x - nearest;
                    } else {
                        if (x < it->first) {
                            if (it->first - x < delta) {
                                nearest = it->first;
                            }

                            break;
                        }

                        nearest = it->first;
                        delta = x - nearest;
                    }
                }

                return grid.at(nearest);
            }
        } else {
            return exactFunction(x);
        }
    }

    // Use Approximation as functor, calls F(x)
    value_t operator()(const double x)
    {
        return F(x);
    }

};

#endif // APPROXIMATION_H
