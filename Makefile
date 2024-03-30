CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRCDIR = .
INCDIR = .
SOURCES = pixel.cc main.cc
TARGET = make

vpath %.h $(INCDIR)

.PHONY: all clean

all: $(TARGET)

make: $(SOURCES:.cc=.o)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	rm -f $(TARGET) $(SOURCES:.cc=.o) main.o 
