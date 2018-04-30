#ifndef __BASIC_TYPE_HPP__
#define __BASIC_TYPE_HPP__

#include <array>

namespace quintuple_go
{

constexpr  int MAP_SIZE = 217;
using      position = int;	
enum class player {EMPTY, ONE, TWO};
using      state    = std::array<player, MAP_SIZE>;

class state_view
{
	state const &tpl;
	std::map<position, player> sp;
public:
	state_view() = default;
	state_view(const state_view & sv) = default;
	state_view(state &s,
			   std::pair<position, player> p,
			   decltype(sp) m = decltype(sp){}): tpl{s},
												 sp{m}   {sp.insert(p);}
	player operator[] (int i) {return sp.find(i) != sp.end()? sp[i]: tpl[i];}
	auto& get_sp() { return sp; }
}

enum      dir { LEFT_UP = 0, LEFT, LEFT_DOWN, RIGHT_DOWN, RIGHT, RIGHT_UP };
constexpr int OUT_OF_BOUND = -1;

class neighbours
{
	std::array<int, 6> _neighbours;

public:
	neighbours(int lu, int l, int ld, int rd, int r, int ru): _neighbours{{lu, l, ld, rd, r, ru}} {}
	int operator [] (dir d) {return _neighbours[d];}
};

std::array<neighbours, MAP_SIZE> const NAB;

}


#endif //__BASIC_TYPE_HPP__
