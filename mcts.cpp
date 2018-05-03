#include "mcts.hpp"

namespace quintuple_go
{

position mcts::best_step() const
{
	return root->best_child();
}


void mcts::reset()
{

}

void mcts::load(state & new_state)
{
    state const &old_state = root->get_const_state();
    position op_pos = OUT_OF_BOUND;
    bool empty = true;
    for (position p = 0; p < MAP_SIZE; p++)
    {
        if (new_state[p] != player::EMPTY)
            empty = false;

        if (old_state[p] != new_state[p])
        {
            op_pos = p;
            break;
        }
    }
	std::lock_guard<std::mutex> guard(root_mtx);

    if (not empty)
        root->set_state(new_state, root, op_pos);
    else
        root->empty_start();
}

void mcts::run(long times)
{
	for (unsigned int count = 0; count < times; count++)
	{
		std::cout << "round #" << count << "\n";
		std::lock_guard<std::mutex> guard(root_mtx);
		node& n = root->select();
		node& child = n.expand();
		player winner = child.simulate();
		child.propagate(winner);
	}
    std::cout << root->best_child() << "\n";
}

}
