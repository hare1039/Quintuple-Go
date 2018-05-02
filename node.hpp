#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <map>
#include <memory>
#include <cmath>
#include <list>
#include <set>

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
		 state_view sv = state_view{get_state()}): _pos{pos},
												   _player{p},
												   _map{(sv)} { _map.insert(std::make_pair(pos, p)); }

	node&  select(int threshold = 20);
	node&  expand();
	player simulate();
	void   propagate(player winner);
	void   set_state(state &s) { std::swap(get_state(), s); }

	position best_child() const;
	void   empty_start();
private:
	double UCT() const;
	int    score() const;
	double win_percentage() const {	return _total == 0? 0.0: _win / _total; }
	int    sum_dir(position start, dir first, dir second, dir scan) const;
	int    sum_oneline(position, dir, player) const;
	void   explore_node(position, dir, int);
	
	struct winner : public std::exception
	{
		player _win;
		position _place;
		winner() = default;
		winner(player p, position pl): _win(p), _place(pl) {}
		const char * what () const noexcept { return "Found winner"; }
	};
	static
	void scan_dir(state_view const & t_map,
				  player me,
				  position start,
				  dir accor,
				  dir direc,
				  std::array<int, MAP_SIZE> &score,
				  bool early_stop = false);
	static player flip(player p) { return (p == player::EMPTY)? player::EMPTY: (p == player::ONE)? player::TWO: player::ONE;}
	static state& get_state() { static state _s; return _s;}
};

	
}

#endif //__NODE_HPP__
