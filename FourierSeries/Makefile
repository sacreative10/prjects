LIBS := -lsfml-graphics -lsfml-window -lsfml-system
cxx := clang++ -g 
CFLAGS := -O3

all: FourierSeries


main.o: src/main.cpp
	$(cxx) -c $(CFLAGS) src/main.cpp -o bin/main.o

FourierSeries: main.o
	$(cxx) bin/main.o $(LIBS) -o bin/FourierSeries