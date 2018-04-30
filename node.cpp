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
			// ____ooox__o___x_xxoo__
			// ___o__________o_______
			if (_map[j] != flipped_player)
				counter++;
			else
				counter = 0;

			if (counter == 5)
			{
				total++;
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

//               avalable space, score of line
// std::tuple<std::deque<position>, int>
static
auto node::scan_dir(state_view const & t_map,
					player who,
					position start,
					dir accor,
					dir direc,
					int limit = -1) const
{
	std::array<std::list<position>, 6> layer;
	player op = flip(who);
	for (position p = start; p != OUT_OF_BOUND; p = NAB[p][accor])
	{
		int counter = 0, op_counter = 0;
		
		for (position walker = p; walker != OUT_OF_BOUND; walker = NAB[walker][direc])
		{
			player play = t_map[walker];
			if (play == who)
				counter++;

			if (play == op)
				op_counter++;
			
			if (limit > counter)
				continue;

			if (counter >= 5)
				throw winner(who);
			if (op_counter >= 5)
				throw winner(op);
			
			layer[counter].push_back(walker);
			limit = std::max(limit, counter);
		}
	}

	for (auto it = layer.rbegin(); it != layer.rend(); --it)
	{
		if (not it->empty())
			return std::make_tuple(*it, layer.rend() - it);
	}
	return std::make_tuple(std::list<position>{}, -1);
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
	state_view t_map{_map};
	/*
	  model:         UP,     UP_LEFT,      DOWN_LEFT,      DOWN,   DOWN_RIGHT,    UP_RIGHT
	  accor:     8 LEFT, 0 LEFT_DOWN, 100 RIGHT_DOWN, 208 RIGHT, 216 RIGHT_UP, 116 LEFT_UP
	  direc: RIGHT_DOWN,       RIGHT,       RIGHT_UP,   LEFT_UP,         LEFT,   LEFT_DOWN
	 */
	player cur = _player;
	for (player p = winner(t_map); p != EMPTY; p = winner(t_map))
	{
		std::multimap<int, std::list<position>, std::greater<int>> avalable;

		try
		{
			int limit = -1;
			std::list<position> t;
			std::tie(t, limit) = scan_dir(t_map, cur,   8,       LEFT, RIGHT_DOWN, limit);
			avalable[limit] = t;
			std::tie(t, limit) = scan_dir(t_map, cur,   0,  LEFT_DOWN,      RIGHT, limit);
			avalable[limit] = t;
			std::tie(t, limit) = scan_dir(t_map, cur, 100, RIGHT_DOWN,   RIGHT_UP, limit);
			avalable[limit] = t;
			std::tie(t, limit) = scan_dir(t_map, cur, 208,      RIGHT,    LEFT_UP, limit);
			avalable[limit] = t;
			std::tie(t, limit) = scan_dir(t_map, cur, 216,   RIGHT_UP,       LEFT, limit);
			avalable[limit] = t;
			std::tie(t, limit) = scan_dir(t_map, cur, 116,    LEFT_UP,  LEFT_DOWN, limit);
			avalable[limit] = t;
		}
		catch (winner &w const)
		{
			return w.winner;
		}
	}
}

	
}
