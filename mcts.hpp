#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include <mutex>
#include "basic_type.hpp"
#include "node.hpp"

namespace quintuple_go
{


class mcts
{
    std::unique_ptr<node> root;
	std::mutex root_mtx;
public:
    mcts():  root(new node(-1, player::TWO)) {};
	position best_step() const;
	void     reset();
	void     load(state &);
	void     run(long i = -1);
};



}
#endif // __MCTS_HPP__
