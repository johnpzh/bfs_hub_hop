# C compiler
ICPC = icpc

ifeq (${debug}, 1)
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -DONEDEBUG
else
#CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -O3 -qopt-report=5 -qopt-report-phase=vec -inline-level=2 -inline-forceinline
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -O3 -inline-level=2 -inline-forceinline
endif

#TARGET = peg_count.o bfs.out
TARGET = bfs.out

.PHONY: clean, all

all: $(TARGET)

#peg_count.o: ../../include/peg_count.h
#	$(ICPC) $(CPPFLAGS) -c $^
#
#bfs.out: bfs.cpp peg_count.o
#	$(ICPC) $(CPPFLAGS) $^ -o $@ 
bfs.out: bfs.cpp
	$(ICPC) $(CPPFLAGS) $^ -o $@ 

clean:
	rm -f $(TARGET)
