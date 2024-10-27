CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall -O2 -Wimplicit-fallthrough

PROG ?= main
OBJS = Creature.o Cavern.o main.o Dragon.o Ghoul.o Mindflayer.o

all: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(EXEC) *.o *.out main 

rebuild: clean all
