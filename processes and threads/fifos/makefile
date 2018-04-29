all: io_mux tx demux pipes

io_mux: io_multiplexer.c handling_functions.o
	gcc -g -Wall io_multiplexer.c handling_functions.o -o io_mux

tx: caps_transmitter.c
	gcc -g -Wall caps_transmitter.c -o tx

demux: demultiplexer.c handling_functions.o
	gcc -g -Wall demultiplexer.c handling_functions.o -o demux

handling_functions.o: handling_functions.h handling_functions.c
	gcc -g -c -Wall handling_functions.c -o handling_functions.o

pipes:
	rm -f T0 T1 T2 T3 T4 T5 T6 T7 T8 T9
	mkfifo T0 T1 T2 T3 T4 T5 T6 T7 T8 T9

clean:
	rm -f T0 T1 T2 T3 T4 T5 T6 T7 T8 T9
	rm -f *.o
	rm -f io_mux tx demux