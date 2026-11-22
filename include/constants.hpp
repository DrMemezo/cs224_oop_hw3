#pragma once
#include <cmath>

const double PI = std::acos(-1); 
const double EPS = 1e-6;
namespace shape_symbols {
    inline constexpr char POINT = 'o';
    inline constexpr char HORIZONTAL = '-';
    inline constexpr char VERTICAL = '|';
    inline constexpr char DIAGONAL_DR = '\\';
    inline constexpr char DIAGONAL_LU = '/';

}
