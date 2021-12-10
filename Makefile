all:
	g++ -pthread src/main.cpp src/map.cpp -o main -lncurses
run:
	./main
