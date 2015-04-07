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
template <typename... Arguments>
class Approximation
{
private:
    static constexpr int N = sizeof...(Arguments);
    std::map<std::array<double, N>, double> grid;
    std::function<double(Arguments...)> exactFunction;

    bool isGridFunction;

    double distance(std::array<double, N> a, std::array<double, N> b);

public:
    Approximation();
    Approximation(std::function<double(Arguments...)> function);
    Approximation(std::map<std::array<double, N>, double> gridFunction);

    double F(double arguments...);
    operator std::function<double(Arguments...)>();

};

#endif // APPROXIMATION_H
