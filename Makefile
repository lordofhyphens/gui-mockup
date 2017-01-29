.PHONY: all clean test

all: harness
test: harness
	./harness
clean: 
	rm -f harness *.o
harness: harness.cpp ConfigGUI.h
	g++ `wx-config --cxxflags --libs` -o $@ $<

