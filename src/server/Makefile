CC=gcc
CFLAGS=-O2 -Wall $(shell pkg-config --cflags glib-2.0 libevent) -Iservice
LIBS=$(shell pkg-config --libs glib-2.0 libevent)


.PHONY = all clean

SOURCES=$(shell ls *.c)


ori:
	${CC} ${CFLAGS} -c cli_arguments.c  -o cli_arguments.o
	${CC} ${CFLAGS} -c configuration.c  -o configuration.o
	${CC} ${CFLAGS} -c service/service.c  -o service/service.o
	${CC} ${CFLAGS} -c service/service_http.c  -o service/service_http.o
	${CC} ${CFLAGS} -c service/service_smtp.c  -o service/service_smtp.o
	${CC} ${CFLAGS} -c service/service_dns.c  -o service/service_dns.o
	${CC} ${CFLAGS} -c main.c -o main.o
	${CC} ${LIBS} cli_arguments.o configuration.o main.o service/service.o service/service_http.o service/service_smtp.o service/service_dns.o -o ogre_c2

clean:
	rm -rfv *.o service/*.o ogre_c2 *~
