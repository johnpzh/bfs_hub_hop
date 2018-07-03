ICPC = icpc

ifeq (${debug}, 1)
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -DONEDEBUG
else
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -O3 -qopt-report=5 -qopt-report-phase=vec
endif


.PHONY: clean

all: undirected.out

undirected.out: undirected.cpp
#icc -mmic -O3 -o undirected undirected.cpp -w
	$(ICPC) $(CPPFLAGS) $^ -o $@

clean:
	rm -f undirected.out
