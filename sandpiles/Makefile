LIBS := -lsfml-graphics -lsfml-window -lsfml-system
cxx := clang++ -g
CFLAGS := -Ofast -std=c++17

all: sandpile

main.o: src/main.cpp
	$(cxx) -c -o main.o src/main.cpp

sandpile: main.o
	$(cxx) -o sandpile main.o $(LIBS)