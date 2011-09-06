#
# Makefile for example programs
#

# to run, execute this first:
# export LD_LIBRARY_PATH=/usr/src/postgresql-9.0.0/src/interfaces/libpq

CC = gcc
GCC = yes
SUN_STUDIO_CC = no
CFLAGS = -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv

# PostgreSQL 9.0 sources
PG9SRC = /usr/src/postgresql-9.0.0/src

#CPPFLAGS += -I/usr/local/pgsql/include
CPPFLAGS += -I$(PG9SRC)/interfaces/libpq -I$(PG9SRC)/include

#LDLIBS += -L/usr/local/pgsql/lib -lpq
LDLIBS += -L$(PG9SRC)/interfaces/libpq -lpq

PROGS = pgstatDatabaseTable
#PROGS = testlibpq testlibpq2 testlibpq3 testlibpq4 testlo

all: $(PROGS)

clean: 
	rm -f $(PROGS)

