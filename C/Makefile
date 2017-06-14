CC = gcc
CFLAGS = -Wall -Wextra -fopenmp -O2 -std=c11 -g `pkg-config --cflags libxml-2.0`
LIBS = `pkg-config --libs libxml-2.0`

program: program.o init_clean.o load.o add.o auxiliary.o queries.o
	@$(CC) $(CFLAGS) program.c -o program init_clean.o load.o add.o auxiliary.o queries.o $(LIBS)

program.o: program.c
	@$(CC) $(CFLAGS) program.c -c

load.o: load.c
	@$(CC) $(CFLAGS) load.c -c

add.o: add.c
	@$(CC) $(CFLAGS) add.c -c

auxiliary.o: auxiliary.c
	@$(CC) $(CFLAGS) auxiliary.c -c

init_clean.o: init_clean.c
	@$(CC) $(CFLAGS) init_clean.c -c

queries.o: queries.c
	@$(CC) $(CFLAGS) queries.c -c

clean:
	@rm -f ./*.o
	@rm -f ./program
