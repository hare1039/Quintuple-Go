#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "mcts.hpp"
#include "basic_type.hpp"

constexpr auto STATE_FILE = "state_7.txt";
constexpr auto STEP_FILE  = "move_7.txt";

auto filesize(const char name[])
{
	std::ifstream i(name, std::ios::ate);
	return i.tellg();
}

int main(int argc, char *argv[])
{
	quintuple_go::mcts tree;
	tree.ready_mtx.lock();
	std::thread th([&tree]{ tree.run(); });
	int pref_line_num = -1;
	for (;;)
	{
		if (filesize(STATE_FILE) > 0)
		{
			using namespace std::literals;
			auto timer = [_s_ = std::chrono::high_resolution_clock::now()]
				{return std::chrono::high_resolution_clock::now() - _s_;};

			std::fstream state(STATE_FILE, std::ios::in);
			int line_num;
			state >> line_num;
			if (pref_line_num != line_num)
			{
				if (pref_line_num > line_num)
				{
					tree.reset();
				}
				std::cout << "File can read\n";
				quintuple_go::state arr;
				for (auto &i : arr)
				{
					int value;
					state >> value;
					i = static_cast<quintuple_go::player>(value);
				}

				tree.load(arr);
				std::cout << "Tree loaded\n";
				tree.ready_mtx.unlock();

                std::this_thread::sleep_for(4.9s - timer());

				auto c = tree.best_step();
				bool outputed = false;
				for (auto &p : c)
				{
					if (arr[p._pos] == quintuple_go::player::EMPTY)
					{
						std::cout << "result: " << p._pos << "\n";
						std::fstream result(STEP_FILE, std::ios::out);
						result << line_num << " " << p._pos;
						pref_line_num = line_num;
						outputed = true;
						break;
					}
				}
				if (not outputed)
				{
					std::set<int> empty;
					for (int i = 0; i < arr.size(); i++)
					{
						if (arr[i] == quintuple_go::player::EMPTY)
							empty.insert(i);
					}


				 	auto it = empty.begin();
					int count = quintuple_go::random_in(static_cast<int>(empty.size() - 1));
					while (count--)
						++it;
					int v = *it;
					std::cout << "guessed result: " << v << "\n";
					std::fstream result(STEP_FILE, std::ios::out);
					result << line_num << " " << v << "\n";
					pref_line_num = line_num;
				}
			}
		}
		else
			std::this_thread::yield();
	}
	return 0;
}
