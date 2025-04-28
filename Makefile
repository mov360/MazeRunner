.default: all

all: mazeRunner

clean:
	rm -f mazeRunner *.o

mazeRunner: Maze.o Agent.o mazeRunner.o Node.o RecursiveBackTracking.o ValidMaze.o EscapeExtension.o
	g++ -Wall -Werror -std=c++17 -g -O -o $@ $^ -lmcpp

%.o: %.cpp
	g++ -Wall -Werror -std=c++17 -g -O -c $^