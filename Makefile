all:
	mkdir -p bin
	g++ -std=c++11 -I include src/canvas.cpp src/main.cpp src/line.cpp src/circle.cpp -o bin/exe
