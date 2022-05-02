all: forests

input.o: input.c input.h
	gcc -Wall -Wextra -Werror -c input.c

functions.o: functions.c functions.h input.h
	gcc -Wall -Wextra -Werror -c functions.c

main.o: main.c functions.h input.h
	gcc -Wall -Wextra -Werror -c main.c

forests: main.o functions.o input.o
	gcc -g -o forests main.o functions.o input.o 

clean:
	rm -f *.o forests