# Warning: you may need more libraries than are included here on the
# build line.  The agent frequently needs various libraries in order
# to compile pieces of it, but is OS dependent and we can't list all
# the combinations here.  Instead, look at the libraries that were
# used when linking the snmpd master agent and copy those to this file.

CC = gcc

OBJECTS = pgstatmibd.o pgstatBgWriter.o
TARGETS = pgstatmibd

CFLAGS = -I. `net-snmp-config --cflags`
BUILDLIBS = `net-snmp-config --libs`
BUILDAGENTLIBS = `net-snmp-config --agent-libs`

# Net-SNMP 5.7 sources
NS5SRC = /usr/src/net-snmp-5.7

override CFLAGS := -I$(NS5SRC)/include $(CFLAGS)
override BUILDAGENTLIBS := -L$(NS5SRC)/agent/.libs -lnetsnmpmibs -lnetsnmpagent -lnetsnmphelpers -L$(NS5SRC)/snmplib/.libs -lnetsnmp $(BUILDAGENTLIBS)

# shared library flags (assumes gcc)
DLFLAGS = -fPIC -shared

all: $(TARGETS)

pgstatmibd: $(OBJECTS)
	$(CC) -o pgstatmibd $(OBJECTS) $(BUILDAGENTLIBS)

clean:
	rm $(OBJECTS) $(TARGETS)

