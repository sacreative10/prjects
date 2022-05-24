LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS := -O3 -std=c++20
CXX := clang++ -g

all: FlappyBirb

NeuralNetwork.o: src/NeuralNetwork.cpp
	$(CXX) $(CFLAGS) -c src/NeuralNetwork.cpp

Bird.o : src/Bird.cpp
	$(CXX) $(CFLAGS) -c -o Bird.o src/Bird.cpp

Pipe.o: src/Pipe.cpp
	$(CXX) $(CFLAGS) -c -o Pipe.o src/Pipe.cpp

main.o : src/main.cpp
	$(CXX) $(CFLAGS) -c -o main.o src/main.cpp

FlappyBirb: NeuralNetwork.o Bird.o Pipe.o main.o
	$(CXX) $(CFLAGS) -o FlappyBirb  NeuralNetwork.o Bird.o Pipe.o main.o $(LIBS)
