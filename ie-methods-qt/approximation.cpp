#include "approximation.h"

#include <QDebug>

Approximation::Approximation()
    : isGridFunction(true)
{ }

Approximation::Approximation(c_fx_ptr &func)
    : exactFunction(func), isGridFunction(false)
{ }

Approximation::Approximation(std::map<Complex, Complex> &gridFunction)
    : grid(gridFunction), isGridFunction(true)
{ }

void Approximation::addXY(const Complex x, const Complex y)
{
    if (isGridFunction) {
        grid[x] = y;
    }
}

Complex Approximation::F(const Complex x)
{
    if (isGridFunction) {
        try {
            return grid.at(x);
        } catch (std::exception e) {
            Complex nearest;

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

Complex Approximation::operator()(const Complex x)
{
    return F(x);
}
/*
Approximation Approximation::operator+(Approximation a)
{
    for (auto it = a.begin(); it != a.end(); it++) {
        try {
            grid.at(a->first);
        } catch (std::exception e) {
            qDebug() << "[WARNING] Summing approximations: different keys." << endl;
            grid[a->first] = a->second;
            continue;
        }

        grid[a->first] += a->second;
    }
}

Approximation Approximation::operator-(Approximation a)
{
    for (auto it = a.begin(); it != a.end(); it++) {
        try {
            grid.at(a->first);
        } catch (std::exception e) {
            qDebug() << "[WARNING] Substracting approximations: different keys." << endl;
            grid[a->first] = -a->second;
            continue;
        }

        grid[a->first] -= a->second;
    }
}

Approximation Approximation::operator*(Approximation a)
{
    for (auto it = a.begin(); it != a.end(); it++) {
        try {
            grid.at(a->first);
        } catch (std::exception e) {
            qDebug() << "[WARNING] Multiplexing approximations: different keys." << endl;
            grid[a->first] = 0.0;
            continue;
        }

        grid[a->first] *= a->second;
    }
}

Approximation Approximation::operator*(Approximation a)
{
    for (auto it = a.begin(); it != a.end(); it++) {
        try {
            grid.at(a->first);
        } catch (std::exception e) {
            qDebug() << "[WARNING] Dividing approximations: different keys." << endl;
            grid[a->first] = 0.0;
            continue;
        }

        grid[a->first] /= a->second;
    }
}
*/
