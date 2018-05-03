#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "mcts.hpp"

int main(int argc, char *argv[])
{
	quintuple_go::mcts tree;
	for (;;)
	{
		quintuple_go::state arr;
		for (auto &i : arr)
		{
			int value;
			std::cin >> value;
			i = static_cast<quintuple_go::player>(value);
		}
        
		tree.load(arr);
        
		tree.run(500);
		std::cout << tree.best_step() << "\n";
	}
	return 0;
}
