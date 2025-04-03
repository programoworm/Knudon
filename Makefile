# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files and target
SOURCES = main.cpp scanner.cpp parser.cpp interpreter.cpp statements.cpp
TARGET = knudon

# Default rule
all: $(TARGET)

# Linking and creating the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean rule
clean:
	rm -f $(TARGET)
