#include "mcts.hpp"

namespace quintuple_go
{

position mcts::best_step() const
{
	return root.best_child();
}


void mcts::reset()
{
	
}

void mcts::load(state & new_state)
{
	std::lock_guard<std::mutex> guard(root_mtx);
	root.set_state(new_state);
}

void mcts::run(long times)
{
	for (unsigned int count = 0; count < times; count++)
	{
		std::cout << "round #" << count << "\n";
		std::lock_guard<std::mutex> guard(root_mtx);
		node& n = root.select();
		node& child = n.expand();
		player winner = child.simulate();
		child.propagate(winner);
        winner = player::EMPTY;
	}
}

}
