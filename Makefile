all:
	g++ -g -Wall -Werror -pthread -o pacman src/main.cpp src/screen.cpp src/utils.cpp src/controllers.cpp -lncursesw
mem:
	g++ -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -Werror -pthread -o main src/main.cpp src/screen.cpp src/utils.cpp src/controllers.cpp -lncursesw
run:
	./pacman
