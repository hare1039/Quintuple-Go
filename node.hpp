#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <map>
#include <memory>

#include "basic_type.hpp"
namespace quintuple_go
{

enum class player {ONE, TWO};
class node
{
	position     _pos;
	player       _player;

	node *       _parent = nullptr;
	int          _win;
	int          _total;
	std::multimap<int, std::unique_ptr<node>, std::greater<int>> _child;
public:
	node(position pos, player p): _pos{pos}, _player{p} {}

	node&  select();
	node&  expand();
	player simulate();
	node&  propagate();

	void   set_state(state &s) { _state = s; }

private:
	double UCT();
	int    score();
	static state& state() { static state _s; return _s;}
};

	
}

#endif //__NODE_HPP__
