#include "approximation.h"

template <typename... Arguments>
double Approximation<Arguments...>::distance(std::array<double, N> a, std::array<double, N> b)
{
    double dist = 0;
    for (int i = 0; i < N; ++i) {
        double d = a[i] - b[i];
        dist += d * d;
    }
    return sqrt(dist);
}

template <typename... Arguments>
Approximation<Arguments...>::Approximation(std::function<double (Arguments...)> function)
    : exactFunction(function), isGridFunction(false)
{ }

template <typename... Arguments>
Approximation<Arguments...>::Approximation(std::map<std::array<double, N>, double> gridFunction)
    : grid(gridFunction), isGridFunction(true)
{ }

template <typename... Arguments>
double Approximation<Arguments...>::F(double arguments...)
{
    if (isGridFunction) {
        std::array<double, N> args(arguments);
        try {
            return grid.at(args);
        } catch (std::exception e) {
            std::array<double, N> nearest;
            double nearestDist;

            for (auto it = grid.begin(); it != grid.end(); it++) {
                if (it == grid.begin()) {
                    nearest = it->first;
                    nearestDist = distance(args, it->first);
                } else {
                    if (distance(args, it->first) < nearestDist) {
                        nearest = grid.begin()->first;
                    }
                }
            }

            return grid.at(nearest);
        }
    } else {
        return exactFunction(arguments);
    }
}

template <typename... Arguments>
Approximation<Arguments...>::operator std::function<double (Arguments...)>()
{
    return F;
}
