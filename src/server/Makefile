CC=gcc
CFLAGS=-O2 -Wall $(shell pkg-config --cflags glib-2.0)
#CFLAGS= -O2 -Wall $(shell pkg-config --cflags glib-2.0 gio-2.0 libevent)
LIBS=$(shell pkg-config --libs glib-2.0)
#LIBS=$(shell pkg-config --libs glib-2.0 gio-2.0 libevent)


.PHONY = all clean

SOURCES=$(shell ls *.c)


ori:
	${CC} ${CFLAGS} -c cli_arguments.c  -o cli_arguments.o
	${CC} ${CFLAGS} -c configuration.c  -o configuration.o
	${CC} ${CFLAGS} -c main.c -o main.o
	${CC} ${LIBS} cli_arguments.o configuration.o main.o -o ori

clean:
	rm -rfv *.o ori *~
