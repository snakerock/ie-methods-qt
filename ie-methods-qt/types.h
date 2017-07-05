#ifndef TYPES_H
#define TYPES_H

template <typename value_t>
class Types {
public:
    using fx_t = std::function<value_t (double)>;
    using fxy_t = std::function<value_t (double, double)>;
};

#endif // TYPES_H
