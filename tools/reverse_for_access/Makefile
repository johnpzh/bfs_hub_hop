ICPC = icpc

ifeq (${debug}, 1)
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -DONEDEBUG
else
	CPPFLAGS = -Wall -Wextra -g -std=c++14 -qopenmp -O3 
endif

.PHONY: clean

TARGET = reverse

all: $(TARGET)

reverse: reverse.cpp
	$(ICPC) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
