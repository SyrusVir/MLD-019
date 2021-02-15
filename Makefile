LIBFLAGS = -lpigpio

% : 
	gcc $@.c -o $@.out MLD019.c -I . -lpigpio 