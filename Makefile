all:
	g++ -g -Wall -Werror -pthread -o main src/main.cpp src/map.cpp src/utils.cpp src/controllers.cpp -lncursesw
mem:
	g++ -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -Werror -pthread -o main src/main.cpp src/map.cpp src/utils.cpp src/controllers.cpp -lncursesw
run:
	./main
