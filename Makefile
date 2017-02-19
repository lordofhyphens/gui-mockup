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
Field.o: Field.cpp Field.hpp
	g++ -c ${CXXFLAGS} `wx-config --cxxflags` -o $@ $<
Option.o: Option.cpp Option.hpp
	g++ -c ${CXXFLAGS} `wx-config --cxxflags` -o $@ $<
harness: harness.o OptionsGroup.o Field.o Option.o
	g++ ${CXXFLAGS} `wx-config --libs` -o $@ $^

