#
# Makefile for example programs
#

CC = gcc
GCC = yes
SUN_STUDIO_CC = no
#CFLAGS = -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv

CPPFLAGS += -I/usr/local/pgsql/include
LDLIBS += -L/usr/local/pgsql/lib -lpq

PROGS = pgstatDatabaseTable
#PROGS = testlibpq testlibpq2 testlibpq3 testlibpq4 testlo

all: $(PROGS)

clean: 
	rm -f $(PROGS)
