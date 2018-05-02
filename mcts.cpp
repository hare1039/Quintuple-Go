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
    for (auto &p : new_state)
        if (p != player::EMPTY)
        {
            root.set_state(new_state);
            return;
        }
    root.empty_start();
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
	}

    auto winner = player::EMPTY;
}

}
