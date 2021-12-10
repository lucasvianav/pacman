all:
	g++ -pthread -o main src/main.cpp src/map.cpp src/utils.cpp src/controllers.cpp -lncurses
run:
	./main
