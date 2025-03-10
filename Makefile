CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
BOOST_LIBS = -lboost_unit_test_framework

# Source files
SRCS = main.cpp Universe.cpp CelestialBody.cpp
OBJS = $(SRCS:.cpp=.o)

all: NBody NBody.a test

NBody: main.o NBody.a
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

NBody.a: Universe.o CelestialBody.o
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: test.cpp NBody.a
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS)

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

clean:
	rm -f *.o NBody NBody.a test

.PHONY: all clean lint test