CXX      = g++
CXXFLAGS = -std=c++14 -pthread -O3
OBJECTS  = mcts.o node.o basic_type.o run debug


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

debug: debug.cpp mcts.o node.o basic_type.o
	$(CXX) $(CXXFLAGS) -o $@ $^
