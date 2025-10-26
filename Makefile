main: src/main.c src/hellofunc.c
		gcc -g -O2 -Wall -Wextra -I. -o main src/main.c src/hellofunc.c -lcrypto