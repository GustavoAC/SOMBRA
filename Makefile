all:
	mkdir -p bin
	g++ -std=c++17 -I include src/canvas.cpp src/main.cpp src/line.cpp src/circle.cpp src/polygon.cpp src/polyline.cpp -Wall -o bin/exe
