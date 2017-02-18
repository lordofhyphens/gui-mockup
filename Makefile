.PHONY: all clean test
CXXFLAGS=--std=c++11
all: harness
test: harness
	./harness
clean: 
	rm -f harness *.o
harness.o: harness.cpp
	g++ -c ${CXXFLAGS} `wx-config --cxxflags` -o $@ $<
OptionsGroup.o: OptionsGroup.cpp OptionsGroup.hpp
	g++ -c ${CXXFLAGS} `wx-config --cxxflags` -o $@ $<
harness: harness.o OptionsGroup.o
	g++ ${CXXFLAGS} `wx-config --libs` -o $@ $^

