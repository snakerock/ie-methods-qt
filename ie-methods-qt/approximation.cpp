#include "approximation.h"

#include <QDebug>

Approximation::Approximation()
    : isGridFunction(true)
{ }

Approximation::Approximation(c_fx_ptr &func)
    : exactFunction(func), isGridFunction(false)
{ }

Approximation::Approximation(std::map<double, Complex> &gridFunction)
    : grid(gridFunction), isGridFunction(true)
{ }

void Approximation::addXY(const double x, const Complex y)
{
    if (isGridFunction) {
        grid[x] = y;
    }
}

Complex Approximation::F(const double x)
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

Complex Approximation::operator()(const double x)
{
    return F(x);
}
