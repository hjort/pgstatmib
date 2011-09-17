#
# Warning: you may need more libraries than are included here on the
# build line.  The agent frequently needs various libraries in order
# to compile pieces of it, but is OS dependent and we can't list all
# the combinations here.  Instead, look at the libraries that were
# used when linking the snmpd master agent and copy those to this
# file.
#

CC = gcc

OBJECTS = example-demon.o example.o delayed_instance.o
TARGETS = example-demon

CFLAGS = -I. `net-snmp-config --cflags`
BUILDLIBS = `net-snmp-config --libs`
BUILDAGENTLIBS = `net-snmp-config --agent-libs`

override CFLAGS := -I/usr/src/net-snmp-5.7/include $(CFLAGS)

# shared library flags (assumes gcc)
DLFLAGS = -fPIC -shared

all: $(TARGETS)

example-demon: $(OBJECTS)
	$(CC) -o example-demon $(OBJECTS) $(BUILDAGENTLIBS)

clean:
	rm $(OBJECTS) $(TARGETS)

test-example:
	snmpwalk localhost enterprises.2021.254
	snmpgetnext localhost ucdavis.254.5

stress:
	for i in `seq 1 3`; do date; snmpget localhost ucdavis.254.5.0; done

test-delayed:
	snmpget localhost 1.3.6.1.4.1.8072.2.1.2.0
