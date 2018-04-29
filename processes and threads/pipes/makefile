processes_mux_tx_demux: main.o libprocesses.a
	gcc -g -Wall main.o -L . -l processes -o processes_mux_tx_demux

main.o: main.c io_multiplexer.h caps_transmitter.h demultiplexer.h
	gcc -g -c -Wall main.c -o main.o

handling_functions.o: handling_functions.h handling_functions.c
	gcc -g -c -Wall handling_functions.c -o handling_functions.o

io_multiplexer.o: io_multiplexer.h io_multiplexer.c
	gcc -g -c -Wall io_multiplexer.c -o io_multiplexer.o

caps_transmitter.o: caps_transmitter.h caps_transmitter.c
	gcc -g -c -Wall caps_transmitter.c -o caps_transmitter.o

demultiplexer.o: demultiplexer.h demultiplexer.c
	gcc -g -c -Wall demultiplexer.c -o demultiplexer.o

libprocesses.a: handling_functions.o io_multiplexer.o caps_transmitter.o demultiplexer.o
	ar -r libprocesses.a handling_functions.o io_multiplexer.o caps_transmitter.o demultiplexer.o

clean:
	rm -f *.o
	rm -f *.a
	rm -f processes_mux_tx_demux