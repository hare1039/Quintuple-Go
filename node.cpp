#include <algorithm>
#include <cmath>
#include <limits>
#include "node.hpp"

namespace quintuple_go
{


// private:
double node::UCT() const
{
	node * n = _parent;
	while (n != nullptr && n->_parent != nullptr)
		n = n->_parent;
	return (_total == 0)? 0:
		static_cast<double>(_win) / _total +
		std::sqrt(2) * std::sqrt(std::log(n->_total) / _total);
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


int node::score_def_dir(dir d) const
{
	int cont = 0;
	player op = flip(_player);
	position mid = NAB[_pos][d];
	while (mid != OUT_OF_BOUND)
    {
        if (_map[mid] == op)
            cont++;
        else
            break;
        mid = NAB[mid][d];
    }
	return cont;
}

int node::score_atk_dir(dir d) const
{
    int cont = 0;
    position mid = NAB[_pos][d];
    while (mid != OUT_OF_BOUND)
    {
        if (_map[mid] == _player)
            cont++;
        else if (_map[mid] != player::EMPTY)
            break;

        if (cont >= 4)
	  throw winner(_player, mid);
        mid = NAB[mid][d];
    }
    return cont;
}

int node::bonus_score() const
{
	int sum = 0;
	sum += (RATE[score_def_dir(LEFT_UP)]);
	sum += (RATE[score_def_dir(LEFT)]);
	sum += (RATE[score_def_dir(LEFT_DOWN)]);
	sum += (RATE[score_def_dir(RIGHT_DOWN)]);
	sum += (RATE[score_def_dir(RIGHT)]);
	sum += (RATE[score_def_dir(RIGHT_UP)]);
    sum += (RATE[score_atk_dir(LEFT_UP)] * 2);
    sum += (RATE[score_atk_dir(LEFT)   ] * 2);
    sum += (RATE[score_atk_dir(LEFT_DOWN)] * 2);
    sum += (RATE[score_atk_dir(RIGHT_DOWN)]* 2);
    sum += (RATE[score_atk_dir(RIGHT)    ] * 2);
    sum += (RATE[score_atk_dir(RIGHT_UP)]  * 2);
	return sum;
}

int node::score() const
{
	int total = 0;
//    total += sum_dir(0,    LEFT_DOWN, RIGHT_DOWN, RIGHT);
//    total += sum_dir(100, RIGHT_DOWN,      RIGHT, RIGHT_UP);
//    total += sum_dir(8,         LEFT,  LEFT_DOWN, RIGHT_DOWN);
	total += bonus_score();
    return total;
}

void node::explore_node(position pos, dir direction, int step = 2)
{
	constexpr int winner_found = -100;
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
            p->_already_win.first  = true;
            p->_already_win.second = w;
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
					std::array<score_pair, MAP_SIZE> &score,
					bool early_stop)
{
	player op = flip(me);
	std::array<int, MAP_SIZE> t_score{};
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

			if (prev == player::EMPTY && play == player::EMPTY)
				counter = 0;

			else if ((prev == me && play == op) || (prev == player::EMPTY && play == op))
				counter = 1;

			else if ((prev == op && play == me) || (prev == player::EMPTY && play == me))
				counter = 2;

			else
				counter += 2;


			if (counter >= 10)
				throw winner(me, walker);
			t_score[walker] += counter;
			score[walker]._total += counter;
		}

		for (counter = 0; NAB[walker][i_direc] != OUT_OF_BOUND; walker = NAB[walker][i_direc])
		{
			player prev = t_map[NAB[walker][direc]];
			player play = t_map[walker];
			if (prev == player::EMPTY && play == player::EMPTY)
				counter = 0;

			else if ((prev == me && play == op) || (prev == player::EMPTY && play == op))
				counter = 1;

			else if ((prev == op && play == me) || (prev == player::EMPTY && play == me))
				counter = 2;

			else
				counter += 2;

			if (counter >= 10)
				throw winner(me, walker);
			t_score[walker] += counter;
			score[walker]._total += counter;
		}
	}

	for (int i = 0; i < t_score.size(); i++)
		score[i]._max = std::max(score[i]._max, t_score[i]);
}

// public
node& node::select(int threshold)
{
//	std::cout << "select\n";
	if (_child.empty() || _already_win.first)
		return *this;
    

	int counter = 0;
	for (auto & c: _child)
	{
		if (c.second->_total == 0)
			return *c.second;
		if (counter++ >= threshold)
			break;
	}

	return (std::max_element(_child.begin(), _child.end(), [](const auto &lhs, const auto &rhs) {
				return lhs.second->UCT() < rhs.second->UCT();
			})->second->select(threshold));
}

node& node::expand()
{
//	std::cout << "expand\n";
    if (_already_win.first)
        return *this;
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
    if (_already_win.first)
        return _already_win.second._win;
    
	state_view t_map{_map};
	/*
	  model:         UP,     UP_LEFT,      DOWN_LEFT,      DOWN,   DOWN_RIGHT,    UP_RIGHT
	  accor:     8 LEFT, 0 LEFT_DOWN, 100 RIGHT_DOWN, 208 RIGHT, 216 RIGHT_UP, 116 LEFT_UP
	  direc: RIGHT_DOWN,       RIGHT,       RIGHT_UP,   LEFT_UP,         LEFT,   LEFT_DOWN
	 */
	player cur = _player;
	for (;;)
	{
        cur = flip(cur);
		std::array<score_pair, MAP_SIZE> score{};
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
					score[p]._max = -1;

			auto max_score = std::max_element(score.begin(), score.end(), [](auto const &lhs, auto const &rhs){
				return lhs._max == rhs._max? lhs._total < rhs._total: lhs._max < rhs._max;
			});

			if (max_score->_max == -1)
                return player::EMPTY;

            std::deque<decltype(max_score)> best_colletion;
            for (auto it = score.begin(); it != score.end(); ++it)
                if (it->_max == max_score->_max && it->_total == max_score->_total)
					best_colletion.push_front(it);
//best_colletion.front();//
            auto avatar = best_colletion[random_in(static_cast<int>(best_colletion.size() - 1))];
//            std::cout << "[ " << avatar - score.begin() << ", " << static_cast<int>(cur) << "\n";
			t_map.insert(std::make_pair(avatar - score.begin(), cur));
		}
		catch (...)
		{
			return player::EMPTY;
		}
	}
    return player::EMPTY;
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

std::deque<node::child_final_info> node::best_child() const
{
	std::deque<child_final_info> candidate;

	for (auto & p: _child)
	{
		candidate.push_back(child_final_info {
			._win = p.second->win_percentage(),
			._UCT = p.second->UCT(),
			._pos = p.second->_pos,
			._score = p.first,
		});
	}
	std::sort(candidate.begin(), candidate.end(), [](auto const &lhs, auto const &rhs) {
		auto lw = lhs._win;
		auto rw = rhs._win;
		auto lu = lhs._UCT;
		auto ru = rhs._UCT;
		if (std::abs(lw - rw) < 0.01)
		{
			if (std::abs(lu - ru) < 0.01)
				return lhs._score > rhs._score;
			else
			    return lu > ru;
		}
		return lw > rw;
	});

	for (auto &s : candidate)
	{
		s.show();
	}
	return candidate;
}

void node::empty_start()
{
    auto p = std::unique_ptr<node>{new node{108, player::ONE, _map}};
    p->_parent = this;
    _child.insert(std::make_pair(108, std::move(p)));
}

void node::set_state(state & s, std::unique_ptr<node> & root)
{
    std::swap(get_state(), s);
    std::unique_ptr<node> n (new node{OUT_OF_BOUND, player::TWO});
	std::swap(n, root);
}

position node::his(state_view t_map)
{
	player cur = player::ONE;
	std::array<score_pair, MAP_SIZE> score{};
	try
	{
		scan_dir(t_map, cur,   8,       LEFT, RIGHT_DOWN, score);
		scan_dir(t_map, cur,   0,  LEFT_DOWN,      RIGHT, score);
		scan_dir(t_map, cur, 100, RIGHT_DOWN,   RIGHT_UP, score);
		scan_dir(t_map, cur, 208,      RIGHT,    LEFT_UP, score, true);
		scan_dir(t_map, cur, 216,   RIGHT_UP,       LEFT, score, true);
		scan_dir(t_map, cur, 116,    LEFT_UP,  LEFT_DOWN, score, true);
		for (auto i = 0; i < score.size(); i++)
		    std::cout << score[i]._max << " ";
		std::cout << "---\n";
	}
	catch (winner const & w)
	{
		return w._place;
	}
	try
	{
		for (position p = 0; p < MAP_SIZE; p++)
			if (t_map[p] != player::EMPTY)
				score[p]._max = -1;

		auto max_score = std::max_element(score.begin(), score.end(), [](auto const &lhs, auto const &rhs){
				return lhs._max == rhs._max? lhs._total < rhs._total: lhs._max < rhs._max;
			});

		if (max_score->_max == -1)
			return 0;

		std::deque<decltype(max_score)> best_colletion;
		for (auto it = score.begin(); it != score.end(); ++it)
			if (it->_max == max_score->_max && it->_total == max_score->_total)
				best_colletion.push_front(it);
// best_colletion.front();
		auto avatar = best_colletion[random_in(static_cast<int>(best_colletion.size() - 1))];
		t_map.insert(std::make_pair(avatar - score.begin(), cur));
		return static_cast<int>(avatar - score.begin());
	}
	catch (...)
	{
		return 0;
	}
}

}
