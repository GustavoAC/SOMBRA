SRCS := src/canvas.cpp src/main.cpp src/line.cpp src/circle.cpp src/polygon.cpp src/polyline.cpp
TINYXML_SRCS := tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinystr.cpp

all:
	mkdir -p bin
	g++ -std=c++17 -I include -I tinyxml ${SRCS} ${TINYXML_SRCS} -Wall -o bin/exe
