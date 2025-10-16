CC := gcc
FLAGS := -std=c99 -Wall -Wextra -Werror

build:
	$(CC) $(FLAGS) -c liste.c
	$(CC) $(FLAGS) -c shapes.c 
	$(CC) $(FLAGS) -c main.c  
	$(CC) $(FLAGS) main.o shapes.o -o main