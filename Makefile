all:
	g++ -Wall -Werror -pthread -o main src/main.cpp src/map.cpp src/utils.cpp src/controllers.cpp -lncursesw
run:
	./main
