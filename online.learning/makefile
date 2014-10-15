# Makefile
global_flags= -g -W -Wall -Wextra -pedantic -Werror
CFLAGS:= $(CFLAGS) $(global_flags) -std=c99
CXXFLAGS:= $(CXXFLAGS) $(global_flags) -std=c++0x
OBJECTS = homework1.o
homework1.app: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CXXFLAGS)
homework1.o: homework1.cc
.PHONY: clean
clean:
	rm *.o *.app
