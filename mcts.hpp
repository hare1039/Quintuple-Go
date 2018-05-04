#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include <mutex>
#include <deque>
#include "basic_type.hpp"
#include "node.hpp"

namespace quintuple_go
{


class mcts
{
public:
    std::unique_ptr<node> root;
	std::mutex mutable root_mtx;
public:
    mcts():     root(new node(-1, player::TWO)) {};
	std::deque<node::child_final_info> best_step() const;
	void        reset();
	void        load(state);
	void        run(ulli i = std::numeric_limits<ulli>::max());
	std::mutex  ready_mtx;
};



}
#endif // __MCTS_HPP__
