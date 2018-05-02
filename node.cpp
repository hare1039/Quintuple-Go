#include <algorithm>
#include <cmath>
#include <limits>
#include "node.hpp"

namespace quintuple_go
{


// private:
double node::UCT() const
{
	return (_total == 0)? 0:
		static_cast<double>(_win) / _total +
		std::sqrt(2) * std::sqrt(std::log((_parent)? _parent /* root */->_total: 0) / _total);
}


int node::sum_oneline(position start, dir scan, player p) const
{
	auto flipped_player = flip(p);
	int total = 0, max_c = 0, max_i = 0, counter = 0, inv_counter = 0;
	for (position i = start; i != OUT_OF_BOUND; i = NAB[i][scan])
	{
		if (_map[i] != flipped_player)
		{
			counter++;
			inv_counter = 0;
		}
		else
		{
			counter = 0;
			inv_counter++;
		}

		if (inv_counter >= 5)
			throw winner(flipped_player, i);

		max_c = std::max(counter, max_c);
		max_i = std::max(inv_counter, max_i);
	}

	total += (RATE[max_c > 5 ? 5: max_c]);
	total -= (RATE[max_i > 5 ? 5: max_i]);
	return total;
}

int node::sum_dir(position start, dir first, dir second, dir scan) const
{
	int total = 0;
	for (position i = 0; i != OUT_OF_BOUND; i = NAB[i][first])
	{
		total += sum_oneline(i, scan, _player);
		total -= sum_oneline(i, scan, flip(_player));
	}
	for (position i = 0; i != OUT_OF_BOUND; i = NAB[i][second])
	{
		total += sum_oneline(i, scan, _player);
		total -= sum_oneline(i, scan, flip(_player));
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
	constexpr int winner_found = MAP_SIZE + 10;
	for (; step != 0; step--)
	{
		position beside = NAB[pos][direction];
		if (beside == OUT_OF_BOUND ||
			_allocated_child.find(beside) != _allocated_child.end() ||
			_allocated_child.find(winner_found) != _allocated_child.end())
			return;
		if (_map[beside] != player::EMPTY)
			continue;

		auto p = std::unique_ptr<node>{new node{beside, flip(_player), _map}};
		p->_parent = this;
		try
		{
			int rank = p->score();
			_child.insert(std::make_pair(rank, std::move(p)));
			_allocated_child.insert(beside);
		}
		catch(winner const &w)
		{
			_allocated_child.insert(winner_found);
			{
				decltype(_child){}.swap(_child);
			}
			_child.insert(std::make_pair(std::numeric_limits<int>::max(), std::move(p)));
			_allocated_child.insert(w._place);
//			std::cout << "winner " << static_cast<int>(w._win) << w._place << "\n";
		}
	}
}

void node::scan_dir(state_view const & t_map,
					player me,
					position start,
					dir accor,
					dir direc,
					std::array<int, MAP_SIZE> &score,
					bool early_stop)
{
	player op = flip(me);
	for (position p = start;
		 p != OUT_OF_BOUND && (not (early_stop && NAB[ NAB[p][accor] ][accor] == OUT_OF_BOUND));
		 p = NAB[p][accor])
	{
        int      counter    = 0;
		position walker     = p;
		dir      i_direc    = inverse(direc);

		for (; NAB[walker][direc] != OUT_OF_BOUND; walker = NAB[walker][direc])
		{
			player prev = t_map[NAB[walker][i_direc]];
			player play = t_map[walker];
			if ((prev == player::EMPTY && play == player::EMPTY) ||
				(static_cast<int>(prev) == OUT_OF_BOUND && play == player::EMPTY))
				counter = 1;
			else if (play == op)
				counter = 0;
			else
				counter++;

			if (counter >= 5)
				throw winner(me, walker);
			score[walker] += counter;
		}

		counter = 0;
		for (; NAB[walker][direc] != OUT_OF_BOUND; walker = NAB[walker][i_direc])
		{
			player prev = t_map[NAB[walker][direc]];
			player play = t_map[walker];
			if ((prev == player::EMPTY && play == player::EMPTY) ||
				(static_cast<int>(prev) == OUT_OF_BOUND && play == player::EMPTY))
				counter = 1;
			else if (play == op)
				counter = 0;
			else
				counter++;

			if (counter >= 5)
				throw winner(me, walker);
			score[walker] += counter;
		}
	}
}

// public
node& node::select(int threshold)
{
//	std::cout << "select\n";
	if (_child.empty())
		return *this;

	int counter = 0;
	for (auto & c: _child)
	{
		if (c.second->_total == 0)
			return *c.second;
		if (counter++ >= threshold)
			break;
	}

	return *(std::max_element(_child.begin(), _child.end(), [](const auto &lhs, const auto &rhs) {
				return lhs.second->UCT() < rhs.second->UCT();
			})->second);
}

node& node::expand()
{
//	std::cout << "expand\n";
	for (position pos = 0; pos < MAP_SIZE; pos++)
	{
		if (_map[pos] != player::EMPTY)
		{
			explore_node(pos, LEFT_UP);
			explore_node(pos, LEFT);
			explore_node(pos, LEFT_DOWN);
			explore_node(pos, RIGHT_DOWN);
			explore_node(pos, RIGHT);
			explore_node(pos, RIGHT_UP);
		}
	}
	return *(_child.begin()->second);
}

player node::simulate()
{
//	std::cout << "simulate\n";
	state_view t_map{_map};
	/*
	  model:         UP,     UP_LEFT,      DOWN_LEFT,      DOWN,   DOWN_RIGHT,    UP_RIGHT
	  accor:     8 LEFT, 0 LEFT_DOWN, 100 RIGHT_DOWN, 208 RIGHT, 216 RIGHT_UP, 116 LEFT_UP
	  direc: RIGHT_DOWN,       RIGHT,       RIGHT_UP,   LEFT_UP,         LEFT,   LEFT_DOWN
	 */
	player cur = _player;
	for (;;)
	{
		std::array<int, MAP_SIZE> score{};
		try
		{
			scan_dir(t_map, cur,   8,       LEFT, RIGHT_DOWN, score);
			scan_dir(t_map, cur,   0,  LEFT_DOWN,      RIGHT, score);
			scan_dir(t_map, cur, 100, RIGHT_DOWN,   RIGHT_UP, score);
			scan_dir(t_map, cur, 208,      RIGHT,    LEFT_UP, score, true);
			scan_dir(t_map, cur, 216,   RIGHT_UP,       LEFT, score, true);
			scan_dir(t_map, cur, 116,    LEFT_UP,  LEFT_DOWN, score, true);
		}
		catch (winner const &w)
		{
			return w._win;
		}

		try
		{
			for (position p = 0; p < MAP_SIZE; p++)
				if (t_map[p] != player::EMPTY)
					score[p] = -1;
			position pos = std::max_element(score.begin(), score.end()) - score.begin();
//			std::cout << "Put @: " << pos << "\n";
			t_map.insert(std::make_pair(pos, cur));
//          t_map.show_sp();
			cur = flip(cur);
		}
		catch (...)
		{
			return player::EMPTY;
		}
	}
}

void node::propagate(player winner)
{
//	std::cout << "propagate\n";
	if (winner == _player)
		_win++;
	_total++;
	if (_parent != nullptr)
		_parent->propagate(winner);
}

position node::best_child() const
{
	return std::max_element(_child.begin(), _child.end(), [](auto const &lhs, auto const &rhs) {
		auto lw = lhs.second->win_percentage();
		auto rw = rhs.second->win_percentage();
		auto lu = lhs.second->UCT();
		auto ru = rhs.second->UCT();
		if (std::abs(lw - rw) < 0.01)
		{
			if (std::abs(lu - ru) < 0.01)
				return lhs.first < rhs.first;
			else
				return lu < ru;
		}

		return lw < rw;
	})->second->_pos;
}


}
