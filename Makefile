CXX      = clang++
CXXFLAGS = -std=c++14 -pthread -g
OBJECTS  = mcts.o node.o basic_type.o run


all: run

run: main.cpp mcts.o node.o basic_type.o
	$(CXX) $(CXXFLAGS) -o $@ $^

mcts.o: mcts.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

node.o: node.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

basic_type.o: basic_type.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJECTS)
