#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include <mutex>
#include "basic_type.hpp"
#include "node.hpp"

namespace quintuple_go
{


class mcts
{
	node root = node(-1, player::ONE);
	std::mutex root_mtx;
public:
	position best_step() const;
	void     reset();
	void     load(state &);
	void     run(long i = -1);
};



}
#endif // __MCTS_HPP__
