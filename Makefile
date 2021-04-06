CC=gcc
CFLAGS = -g -c -O -Wall -Wextra
LIBFLAGS = -lpigpio 

MLD019.o: MLD019.c MLD019.h
	$(CC) $(CFLAGS) $< -I. $(LIBFLAGS)

%:
	gcc $@.c -o $@.out MLD019.c -I . $(LIBFLAGS) -lcurses

.PHONY: clean
clean:
	rm -f *.o *.gch