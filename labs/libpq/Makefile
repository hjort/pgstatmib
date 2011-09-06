#
# Makefile for example programs
#

# Compilers
CC = gcc
GCC = yes
SUN_STUDIO_CC = no
CFLAGS = -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv

pgsql_sources = /usr/src/postgresql-9.0.0/src
libpq_srcdir = $(pgsql_sources)/interfaces/libpq

CPPFLAGS := -I$(pgsql_sources)/include -D_GNU_SOURCE -I$(pgsql_sources)/port -Wl,--as-needed -Wl,-rpath,'/usr/local/pgsql/lib',--enable-new-dtags -L$(pgsql_sources)/port -lpgport -L$(libpq_srcdir) -lpq

#gcc -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv -I../../../src/interfaces/libpq -I../../../src/include -D_GNU_SOURCE  -L../../../src/port -Wl,--as-needed -Wl,-rpath,'/usr/local/pgsql/lib',--enable-new-dtags  testlibpq.c  -L../../../src/port -lpgport -L../../../src/interfaces/libpq -lpq  -o testlibpq

#gcc -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv -I/usr/src/postgresql-9.0.0/src/interfaces/libpq -I/usr/src/postgresql-9.0.0/src/include -D_GNU_SOURCE -I/usr/src/postgresql-9.0.0/src/port -Wl,--as-needed -Wl,-rpath,'/usr/local/pgsql/lib',--enable-new-dtags testlibpq.c -L/usr/src/postgresql-9.0.0/src/port -lpgport -L/usr/src/postgresql-9.0.0/src/interfaces/libpq -lpq -o testlibpq

#subdir = src/test/examples
#top_builddir = ../../..
#include $(top_builddir)/src/Makefile.global

ifeq ($(PORTNAME), win32)
LDLIBS += -lws2_32
endif

override CPPFLAGS := -I$(libpq_srcdir) $(CPPFLAGS)
override LDLIBS := $(libpq_pgport) $(LDLIBS)


PROGS = testlibpq testlibpq2 testlibpq3 testlibpq4 testlo

all: 
#$(PROGS)
	gcc -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv -I/usr/src/postgresql-9.0.0/src/interfaces/libpq -I/usr/src/postgresql-9.0.0/src/include -D_GNU_SOURCE -I/usr/src/postgresql-9.0.0/src/port -Wl,--as-needed -Wl,-rpath,'/usr/local/pgsql/lib',--enable-new-dtags testlibpq.c -L/usr/src/postgresql-9.0.0/src/port -lpgport -L/usr/src/postgresql-9.0.0/src/interfaces/libpq -lpq -o testlibpq

clean: 
	rm -f $(PROGS)
