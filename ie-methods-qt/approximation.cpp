#include "approximation.h"

#include <QDebug>

Approximation::Approximation()
    : isGridFunction(true)
{ }

Approximation::Approximation(std::function<double (double)> &func)
    : exactFunction(func), isGridFunction(false)
{ }

Approximation::Approximation(std::map<double, double> &gridFunction)
    : grid(gridFunction), isGridFunction(true)
{ }

void Approximation::addXY(double x, double y)
{
    if (isGridFunction) {
        grid[x] = y;
    }
}

double Approximation::F(double arguments)
{
    if (isGridFunction) {
        try {
            return grid.at(arguments);
        } catch (std::exception e) {
            double nearest;

            for (auto it = grid.begin(); it != grid.end(); it++) {
                if (it == grid.begin()) {
                    nearest = it->first;
                } else {
                    if (arguments < it->first) {
                        break;
                    }
                }
            }

            return grid.at(nearest);
        }
    } else {
        return exactFunction(arguments);
    }
}

double Approximation::operator()(double arguments)
{
    return F(arguments);
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
