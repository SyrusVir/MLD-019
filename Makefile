LIBFLAGS = -lpigpio -lcurses


%:
	gcc $@.c -o $@.out MLD019.c -I . $(LIBFLAGS) 