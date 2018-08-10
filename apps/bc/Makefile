# C compiler
#CXX = icpc
CXX = g++

ifeq (${debug}, 1)
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -DONEDEBUG
else
	#CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -O3 -qopt-report=5 -qopt-report-phase=vec -inline-level=2 -inline-forceinline
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -fopenmp
endif

LIB = -I/scratch/zpeng.scratch/pppp/networkit-git/include -L/scratch/zpeng.scratch/pppp/networkit-git -lNetworKit

TARGET = bc.out

.PHONY: clean, all

all: $(TARGET)

#peg_count.o: ../../include/peg_count.h
#	$(ICPC) $(CPPFLAGS) -c $^

bc.out: bc.cpp
#$(CXX) $(CPPFLAGS) $(LIB) $^ -o $@ 
	$(CXX) -o $@ $(CPPFLAGS) $^ $(LIB)
#$(CXX) -o $@ -std=c++14 -I/scratch/zpeng.scratch/pppp/networkit-git/include -L/scratch/zpeng.scratch/pppp/networkit-git $^ -lNetworKit -fopenmp

clean:
	rm -f $(TARGET)
