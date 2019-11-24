# PROYECTO - Makefile 
# 
CXXFLAGS := -std=c++11 -g
LIBS := -lm -lGL -lGLU -lglut
HEADERS := Food.h World.h Snake.h
OBJS := main.o Food.o World.o Snake.o

all: main

main: $(OBJS) $(HEADERS)
	g++ $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.cxx
	g++ $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean: 
	rm -r *.o main

## eof - makefile
