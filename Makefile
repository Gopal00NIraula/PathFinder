# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source and object files
SRCS = main.cpp MazeGenerator.cpp PathfinderBFS.cpp disjointSet.cpp output.cpp
OBJS = main.o MazeGenerator.o PathfinderBFS.o disjointSet.o output.o

# Output executable name
TARGET = Project3

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

MazeGenerator.o: MazeGenerator.cpp MazeGenerator.h
	$(CXX) $(CXXFLAGS) -c MazeGenerator.cpp

PathfinderBFS.o: PathfinderBFS.cpp PathfinderBFS.h
	$(CXX) $(CXXFLAGS) -c PathfinderBFS.cpp

disjointSet.o: disjointSet.cpp disjointSet.h
	$(CXX) $(CXXFLAGS) -c disjointSet.cpp

output.o: output.cpp pathfinder.h
	$(CXX) $(CXXFLAGS) -c output.cpp

# Clean object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
