#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <map>
#include <memory>
#include <cmath>
#include <list>

#include "basic_type.hpp"
#include "state_view.hpp"
namespace quintuple_go
{


class node
{
	position     _pos;
	player       _player;

	node *       _parent = nullptr;
	int          _win    = 0;
	int          _total  = 0;
	state_view   _map;
	std::set<position> _allocated_child;
	std::multimap<int, std::unique_ptr<node>, std::greater<int>> _child;
public:
	node(position pos,
		 player p,
		 state_view sv = state_view{state(), {-1, -1}}): _pos{pos},
														 _player{p},
														 _map{(sv)} {}

	node&  select();
	node&  expand();
	player simulate();
	node&  propagate();
	void   set_state(state &s) { std::swap(state(), s); }

private:
	double UCT() const;
	int    score() const;
	int    sum_dir(position start, dir first, dir second, dir scan) const;
	void   explore_node(position, dir, int);
	// std::tuple<std::deque<position>, int>
	struct winner : public exception
	{
		player winner;
		winner() = default;
		winner(player p): winner(p) {}
		const char * what () const noexcept { return "Found winner"; }
	};
	static auto scan_dir(state_view const & t_map,
						 player who,
						 position start,
						 dir accor,
						 dir direc,
						 int limit = -1) const;
	static player flip(player p) { return (p == EMPTY)? EMPTY: (p == ONE)? TWO: ONE;}
	static state& state() { static state _s; return _s;}
};

	
}

#endif //__NODE_HPP__
