#ifndef __STATE_VIEW_HPP__
#define __STATE_VIEW_HPP__

#include <map>
#include "basic_type.hpp"

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
	state state() { state s; for (int i = 0; i < MAP_SIZE; i++) s[i] = (*this)[i]; return s;}
}

#endif // __STATE_VIEW_HPP__
