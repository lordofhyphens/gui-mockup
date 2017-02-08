.PHONY: all clean test valgrind

all: harness
test: harness
	@./harness
valgrind: harness
	valgrind --leak-check=full ./$<
clean: 
	rm -f harness *.o
harness: harness.cpp ConfigGUI.h
	g++ -std=c++11 `wx-config --cxxflags --libs` -o $@ $<

