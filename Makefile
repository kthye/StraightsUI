CXX= g++
CXXFLAGS = -std=c++14 -Wall -MMD -g `pkg-config gtkmm-3.0 --cflags`
LDFLAGS=`pkg-config gtkmm-3.0 --libs`
SOURCES = $(filter-out controller_test_1.cpp, $(wildcard *.cpp)) # list of all .cpp files in the current directory
#SOURCES = $(filter-out main.cpp, $(wildcard *.cpp))
OBJECTS = $(SOURCES:.cpp=.o)  # .o files depend upon .cpp files with same names
DEPENDS = $(OBJECTS:.o=.d)   # .d file is list of dependencies for corresponding .cpp file
EXEC = straights

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

-include $(DEPENDS)

.PHONY: clean

clean:
	rm $(EXEC) $(OBJECTS) $(DEPENDS)
