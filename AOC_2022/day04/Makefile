.SILENT:

CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++17 -O2
CXX_DEBUG_FLAGS = -Wall -Werror -std=c++17 -g
INCLUDES = -I ..
BIN = bin

default: p1r p2r
all: p1 p1r p1g p2 p2r p2g

%: %.cpp ../aoc_utils.cpp
	mkdir -p ${BIN}
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $^ -o ${BIN}/$@

%.nostrip: %.cpp ../aoc_utils.cpp
	mkdir -p ${BIN}
	$(CXX) $(CXX_DEBUG_FLAGS) $(INCLUDES) $^ -o ${BIN}/$@

p1 : puzzle1
p2 : puzzle2

p1r : p1
	${BIN}/puzzle1
p2r : p2
	${BIN}/puzzle2

p1g : puzzle1.nostrip
p2g : puzzle2.nostrip
