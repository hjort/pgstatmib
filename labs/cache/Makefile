# Warning: you may need more libraries than are included here on the
# build line.  The agent frequently needs various libraries in order
# to compile pieces of it, but is OS dependent and we can't list all
# the combinations here.  Instead, look at the libraries that were
# used when linking the snmpd master agent and copy those to this file.

CC = gcc
GCC = yes

OBJECTS = example-demon.o pgstatDatabaseTable.o
TARGETS = example-demon

CFLAGS = -I. `net-snmp-config --cflags` `pg_config --cflags`
BUILDLIBS = `net-snmp-config --libs` `pg_config --libs`
BUILDAGENTLIBS = `net-snmp-config --agent-libs`

all: $(TARGETS)

pgstatmibd: $(OBJECTS)
	$(CC) -o example-demon $(OBJECTS) $(BUILDAGENTLIBS) $(LDLIBS)

clean:
	rm $(OBJECTS) $(TARGETS)

