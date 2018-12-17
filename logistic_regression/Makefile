CFLAGS = -Wall -g -I/home/chen/workspace/PowerGraph/deps/local/include
LIBS  = -lm
CXX=/usr/bin/g++-6
SRCS = $(wildcard *.cpp)

main: main.cpp gd.h read_file.h
	$(CXX) $(CFLAGS) -o $@ $<  $(LIBS)