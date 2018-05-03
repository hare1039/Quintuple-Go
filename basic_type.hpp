#ifndef __BASIC_TYPE_HPP__
#define __BASIC_TYPE_HPP__

#include <array>
#include <random>
#include <iostream>
#include <initializer_list>


namespace quintuple_go
{

constexpr  int MAP_SIZE = 217;
using      position = int;
enum class player {EMPTY, ONE, TWO};
using      state    = std::array<player, MAP_SIZE>;

enum       dir { LEFT_UP = 0, LEFT, LEFT_DOWN, RIGHT_DOWN, RIGHT, RIGHT_UP };
constexpr  int OUT_OF_BOUND = (-1);

class neighbours
{
	std::array<int, 6> _neighbours;

public:
	neighbours(int lu, int l, int ld, int rd, int r, int ru): _neighbours{{lu, l, ld, rd, r, ru}} {}
	int operator [] (dir d) const {return _neighbours[d];}
};

extern std::array<neighbours, MAP_SIZE> const NAB;
extern std::array<int, 9> const RATE;
bool random_break(double p);
bool random_in(int max);
template<typename T>
T random_gen(std::initializer_list<std::pair<T, double>> l)
{
    auto selected = l.begin();
    double prev_pos = 1;
    for (; selected != l.end(); ++selected)
        if (random_break(selected->second / prev_pos))
            break;
        else
            prev_pos *= selected->second;

    return selected == l.end()? (--selected)->first: selected->first;
}
using ulli = unsigned long long int;
constexpr dir inverse(dir d) { return static_cast<dir>((static_cast<int>(d) + 3) % 6);}

}


#endif //__BASIC_TYPE_HPP__
