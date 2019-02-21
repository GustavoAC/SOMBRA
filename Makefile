all:
	g++ -std=c++11 -I include src/canvas.cpp src/main.cpp src/line.cpp -o bin/exe