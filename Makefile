.PHONY: all clean test
LIBS=`wx-config --libs`
CXXFLAGS=-std=c++11 `wx-config --cxxflags` -Ilibslic3r
all: harness
test: harness
	./harness
clean: 
	rm -f harness *.o
OptionsGroup.o: OptionsGroup.cpp OptionsGroup.hpp
	g++ -c ${CXXFLAGS} -o $@ $<
Field.o: Field.cpp Field.hpp
	g++ -c ${CXXFLAGS} -o $@ $<
harness.o: harness.cpp
	g++ -c ${CXXFLAGS} -o $@ $<
harness: OptionsGroup.o Field.o harness.o
	g++ ${CXXFLAGS} ${LIBS} -o $@ $^

