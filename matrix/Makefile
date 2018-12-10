all : main.c matrix.c matrix.h
	gcc main.c matrix.c -o matrix -lm -Wall --std=c89

pset : pset.c matrix.c matrix.h
	gcc pset.c matrix.c -o pset -lm -Wall --std=c89

clean :
	rm pset matrix pset.exe matrix.exe pset.o matrix.o