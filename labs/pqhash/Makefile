CPPFLAGS = -I`pg_config --includedir` -g
LDLIBS = -lpq

PROGS = tablestats

all: $(PROGS)

clean: 
	rm -f $(PROGS)

test:
	sudo su postgres -c ./tablestats
