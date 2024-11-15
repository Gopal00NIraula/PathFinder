Project3: main.o MazeGenerator.o PathfinderBFS.o disjointSet.o Sampler.o output.o
	g++ -std=c++11 -Wall -o project3 main.o MazeGenerator.o PathfinderBFS.o disjointSet.o Sampler.o output.o

main.o: main.cpp MazeGenerator.h PathfinderBFS.h pathfinder.h
	g++ -c -std=c++11 -Wall main.cpp

MazeGenerator.o: MazeGenerator.cpp MazeGenerator.h disjointSet.h Sampler.h pathfinder.h
	g++ -c -std=c++11 -Wall MazeGenerator.cpp

PathfinderBFS.o: PathfinderBFS.cpp PathfinderBFS.h pathfinder.h
	g++ -c -std=c++11 -Wall PathfinderBFS.cpp

disjointSet.o: disjointSet.cpp disjointSet.h
	g++ -c -std=c++11 -Wall disjointSet.cpp

Sampler.o: Sampler.cpp Sampler.h
	g++ -c -std=c++11 -Wall Sampler.cpp

output.o: output.cpp pathfinder.h
	g++ -c -std=c++11 -Wall output.cpp

clean:
	rm -f *.o project3
