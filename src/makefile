instrument: instrument.o input.o calc.o data.o
	gcc -Wall -std=c99 -o instrument instrument.o input.o calc.o data.o -lncurses `pkg-config --cflags --libs jack`
instrument.o: instrument.c instrument.h
	gcc -Wall -std=c99 -c instrument.c -g `pkg-config --cflags --libs jack`
input.o: input.c input.h
	gcc -std=c99 -Wall -c input.c -g -lncurses
#output.o: output.c output.h
#	gcc -std=c99 -Wall -c output.c -g -lncurses
calc.o: calc.c calc.h
	gcc -std=c99 -Wall -c calc.c -g -lncurses
data.o: data.c data.h
	gcc -std=c99 -Wall -c data.c -g -lncurses
#utility_functions.o: utility_functions.c utility_functions.h
#	gcc -std=c99 -Wall -c utility_functions.c -g -lncurses
clean:
	rm -f *.o instrument core
