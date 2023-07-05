CXX=g++

all: build

build:
	$(CXX) -std=c++11 -o main main.cpp Memory.cpp Processor.cpp Slot.cpp

run:
	@./main
