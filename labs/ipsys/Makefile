# Warning: you may need more libraries than are included here on the
# build line.  The agent frequently needs various libraries in order
# to compile pieces of it, but is OS dependent and we can't list all
# the combinations here.  Instead, look at the libraries that were
# used when linking the snmpd master agent and copy those to this file.

CC = gcc
GCC = yes

OBJECTS = example-demon.o ipSystemStatsTable.o
TARGETS = example-demon

CFLAGS = -I. `net-snmp-config --cflags` -I/usr/src/net-snmp/include
BUILDLIBS = `net-snmp-config --libs`
BUILDAGENTLIBS = `net-snmp-config --agent-libs`

all: $(TARGETS)

example-demon: $(OBJECTS)
	$(CC) -o example-demon $(OBJECTS) $(BUILDAGENTLIBS) $(LDLIBS)

clean:
	rm -f $(OBJECTS) $(TARGETS) *.o

agent-start: example-demon
	sudo ./example-demon

client-test:
	#snmpwalk localhost ipSystemStats
	snmpwalk localhost 1.3.6.1.4.1.27645.3.51
