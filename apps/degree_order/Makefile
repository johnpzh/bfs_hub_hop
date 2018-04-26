# C compiler
ICPC = icpc

ifeq (${debug}, 1)
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -DONEDEBUG
else
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -O3 -qopt-report=5 -qopt-report-phase=vec -inline-level=2 -inline-forceinline
endif

TARGET = bfs.out

.PHONY: clean, all

all: $(TARGET)

bfs.out: bfs.cpp 
	$(ICPC) $(CPPFLAGS) $^ -o $@ 


clean:
	rm -f $(TARGET)
