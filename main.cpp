#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "mcts.hpp"

constexpr auto STATE_FILE = "state_07.txt";
constexpr auto STEP_FILE  = "move_07.txt";

auto filesize(const char name[])
{
	std::ifstream i(name, std::ios::ate);
	return i.tellg();
}

int main(int argc, char *argv[])
{
	quintuple_go::mcts tree;
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
				quintuple_go::state arr;
				for (auto &i : arr)
				{
					int value;
					state >> value;
					i = static_cast<quintuple_go::player>(value);
				}

				tree.load(arr);

				while (timer() < 4.9s)
					std::this_thread::yield();				

				std::cout << "out\n";
				std::fstream result(STEP_FILE, std::ios::out);
				result << line_num << " " << tree.best_step();
				pref_line_num = line_num;
			}
		}
		else
			std::this_thread::yield();
	}
	th.join();
	return 0;
}
