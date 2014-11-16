SRCS=srcs/*.cpp
PARAMS=-std=c++0x -lwiringPi -Wall
OUT=-o bin/log

all: cpp
dir: ; mkdir -p bin
cpp: dir ; g++ $(SRCS) $(PARAMS) $(OUT)
clean: rm -rf bin

