CXX = g++
CXXFLAGS = -Wall -g
SOURCES = ./main.cpp  ./getblk.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
