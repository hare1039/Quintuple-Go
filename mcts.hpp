#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include "basic_type.hpp"
#include "node.hpp"

namespace quintuple_go
{


class mcts
{
	node root;
public:
	position best_step() const;
	void     reset();
	void     load(state const &);
	void     run();
};












}
#endif // __MCTS_HPP__
