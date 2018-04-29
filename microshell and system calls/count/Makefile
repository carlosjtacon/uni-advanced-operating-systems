count: main.o libcount.a
	gcc -g -Wall main.o -L . -l count -o count

main.o: main.c readchar_R.h count_M.h
	gcc -g -c -Wall main.c -o main.o

readchar_R.o: readchar_R.c readchar_R.h
	gcc -g -c -Wall readchar_R.c -o readchar_R.o

count_M.o: count_M.c count_M.h
	gcc -g -c -Wall count_M.c -o count_M.o

libcount.a: readchar_R.o count_M.o
	ar -r libcount.a readchar_R.o count_M.o

clean:
	rm -f *.o
	rm -f libcount.a
	rm -f count