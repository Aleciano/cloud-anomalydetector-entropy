CPP=g++
CFLAGS=-Wall -fpermissive
#INCLUDEs sobrecarregados
INCLUDE=-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/local/include/libgtop-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libgtop-2.0

#all: compilar 

#compilar: filaDouble.o filaShortInt.o cpuinfo.o
#	$(CPP) -o 

localmetrics.o: localmetrics.cpp filaEncDouble.c filaEncShortInt.c
	$(CPP) $(INCLUDE) -o $@ $(CFLAGS) $^ -lgtop-2.0 -lglib-2.0
