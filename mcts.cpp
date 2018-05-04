#include "mcts.hpp"

namespace quintuple_go
{

std::deque<node::child_final_info> mcts::best_step() const
{
	std::lock_guard<std::mutex> guard(root_mtx);
	return root->best_child();
}


void mcts::reset()
{
	ready_mtx.lock();
	std::unique_ptr<node> n(new node(-1, player::TWO));
	state s{};
	root->set_state(s, n, OUT_OF_BOUND);
}

void mcts::load(state new_state)
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

void mcts::run(ulli times)
{
	for (unsigned int count = 0; count < times; count++)
	{
		if (count % 10000 == 0)
			std::cout << "round #" << count / 10000 << "\n";
		std::lock(root_mtx, ready_mtx);

		std::lock_guard<std::mutex> lock1( root_mtx, std::adopt_lock);
		std::lock_guard<std::mutex> lock2(ready_mtx, std::adopt_lock);

		node& n = root->select();
		node& child = n.expand();
		player winner = child.simulate();
		child.propagate(winner);
	}
}

}
