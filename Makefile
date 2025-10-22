main: main.c hellofunc.c
		gcc -O2 -Wall -Wextra -I. -o main main.c hellofunc.c -lcrypto