# Variables for the compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# The target executable
TARGET = my_program

# Source files
SRCS = main.cpp ranking_class.cpp player_class.cpp wimbledon_class.cpp match_class.cpp round_class.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# The first target is the default target that 'make' will run
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean run
