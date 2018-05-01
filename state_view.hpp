#ifndef __STATE_VIEW_HPP__
#define __STATE_VIEW_HPP__

#include <map>
#include "basic_type.hpp"

namespace quintuple_go
{

class state_view
{
	state const &tpl;
	std::map<position, player> sp;
public:
	state_view() = default;
	state_view(const state_view & sv) = default;
	state_view(state &s,
			   std::pair<position, player> p = decltype(p){-1, player::EMPTY},
			   decltype(sp) m = decltype(sp){}): tpl{s},
												 sp{m}   {sp.insert(p);}
	player operator[] (int i) const { return sp.find(i) != sp.end()? sp.find(i)->second: tpl[i]; }
	auto   insert(std::pair<position, player> && p) { return sp.insert(p); }
	auto&  get_sp() { return sp; }
	state  gen_state()  { state s; for (int i = 0; i < MAP_SIZE; i++) s[i] = (*this)[i]; return s;}
	void   show_sp()    { for (auto &v: sp) std::cout << v.first << ": " << static_cast<int>(v.second) << "\n"; }
};


}
#endif // __STATE_VIEW_HPP__
