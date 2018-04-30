#include "node.hpp"

namespace quintuple_go
{


// private:
double node::UCT()
{
	return (total == 0)? std::numeric_limits<double>::max():
		static_cast<double>(_win) / _total +
		std::sqrt(2) * std::sqrt(std::log((_parent)? _parent->_total: 0) / _total);
}

int node::sum_dir(position start, dir first, dir second, dir scan) const
{
	int total = 0, counter = 0;
	auto flipped_player = filp(_player);
	for (position i = 0; i != OUT_OF_BOUND; i = NAB[i][first])
		for (position j = i; j != OUT_OF_BOUND; j = NAB[j][scan])
		{
			if (_map[j] != flipped_player)
				counter++;
			else
				counter = 0;

			if (counter == 5)
			{
				total++;
				counter--;
			}
		}
	counter = 0;
	for (position i = 0; i != OUT_OF_BOUND; i = NAB[i][second])
		for (position j = i; j != OUT_OF_BOUND; j = NAB[j][scan])
		{
			if (_map[j] != flipped_player)
				counter++;
			else
				counter = 0;

			if (counter == 5)
			{
				total++;
				counter--;
			}
		}

	return total;
}


int node::score() const
{
	int total = 0;
	total += sum_dir(0,    LEFT_DOWN, RIGHT_DOWN, RIGHT);
	total += sum_dir(100, RIGHT_DOWN,      RIGHT, RIGHT_UP);
	total += sum_dir(8,         LEFT,  LEFT_DOWN, RIGHT_DOWN);
	return total;
}

void node::explore_node(position pos, dir direction, int step = 2)
{
	for (; step != 0; step--)
	{
		position beside = NAB[pos][direction];
		if (beside == OUT_OF_BOUND ||
			_allocated_child.find(beside) != _allocated_child.end())
			return;
		if (_map[beside] != EMPTY)
			continue;
		
		auto p = std::unique_ptr<node>{new node{beside, flip(_player), _map.get_sp()}};
		int rank = p->score();
		_child[rank] = std::move(p);
		_allocated_child.insert(beside);
	}
}
// public
node& node::select()
{
	if (_child.empty())
		*this;
	return *_child.begin();
}

node& node::expand()
{
	for (position pos = 0; pos < MAP_SIZE; pos++)
	{
		player& stone = _map[pos];
		if (stone != EMPTY)
		{
			explore_node(stone, LEFT_UP);
			explore_node(stone, LEFT);
			explore_node(stone, LEFT_DOWN);
			explore_node(stone, RIGHT_DOWN);
			explore_node(stone, RIGHT);
			explore_node(stone, RIGHT_UP);
		}
	}
}

player node::simulate()
{
	
}

	
}
