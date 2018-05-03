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
	std::mutex mutable root_mtx;
public:
    mcts():     root(new node(-1, player::TWO)) {};
	position    best_step() const;
	void        reset();
	void        load(state &);
	void        run(ulli i = std::numeric_limits<ulli>::max());
	std::mutex  ready_mtx;
};



}
#endif // __MCTS_HPP__
