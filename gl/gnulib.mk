## DO NOT EDIT! GENERATED AUTOMATICALLY!
## Process this file with automake to produce Makefile.in.
# Copyright (C) 2004-2007 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
# Reproduce by: gnulib-tool --import --dir=. --local-dir=gl/override --lib=libgnu --source-base=gl --m4-base=gl/m4 --doc-base=doc --aux-dir=. --avoid=snprintf --avoid=vasnprintf --makefile-name=gnulib.mk --libtool --macro-prefix=gl arpa_inet fdl gendocs getaddrinfo getline getpass gpl inet_ntop inet_pton lgpl maintainer-makefile readline


MOSTLYCLEANFILES += core *.stackdump

noinst_LTLIBRARIES += libgnu.la

libgnu_la_SOURCES =
libgnu_la_LIBADD = $(gl_LTLIBOBJS)
libgnu_la_DEPENDENCIES = $(gl_LTLIBOBJS)
EXTRA_libgnu_la_SOURCES =
libgnu_la_LDFLAGS = $(AM_LDFLAGS)

## begin gnulib module arpa_inet

BUILT_SOURCES += $(ARPA_INET_H)

# We need the following in order to create <arpa/inet.h> when the system
# doesn't have one.
arpa/inet.h:
	test -d arpa || mkdir arpa
	rm -f $@-t $@
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  echo '#include <sys/socket.h>'; \
	} > $@-t
	mv $@-t $@
MOSTLYCLEANFILES += arpa/inet.h arpa/inet.h-t
MOSTLYCLEANDIRS += arpa

## end   gnulib module arpa_inet

## begin gnulib module getaddrinfo


EXTRA_DIST += gai_strerror.c getaddrinfo.c getaddrinfo.h

EXTRA_libgnu_la_SOURCES += gai_strerror.c getaddrinfo.c

## end   gnulib module getaddrinfo

## begin gnulib module getdelim


EXTRA_DIST += getdelim.c getdelim.h

EXTRA_libgnu_la_SOURCES += getdelim.c

## end   gnulib module getdelim

## begin gnulib module getline


EXTRA_DIST += getline.c getline.h

EXTRA_libgnu_la_SOURCES += getline.c

## end   gnulib module getline

## begin gnulib module getpass


EXTRA_DIST += getpass.c getpass.h

EXTRA_libgnu_la_SOURCES += getpass.c

## end   gnulib module getpass

## begin gnulib module gettext-h

libgnu_la_SOURCES += gettext.h

## end   gnulib module gettext-h

## begin gnulib module inet_ntop


EXTRA_DIST += inet_ntop.c inet_ntop.h

EXTRA_libgnu_la_SOURCES += inet_ntop.c

## end   gnulib module inet_ntop

## begin gnulib module inet_pton


EXTRA_DIST += inet_pton.c inet_pton.h

EXTRA_libgnu_la_SOURCES += inet_pton.c

## end   gnulib module inet_pton

## begin gnulib module netinet_in

BUILT_SOURCES += $(NETINET_IN_H)

# We need the following in order to create <netinet/in.h> when the system
# doesn't have one.
netinet/in.h:
	test -d netinet || mkdir netinet
	rm -f $@-t $@
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  echo '#include <sys/socket.h>'; \
	} > $@-t
	mv $@-t $@
MOSTLYCLEANFILES += netinet/in.h netinet/in.h-t
MOSTLYCLEANDIRS += netinet

## end   gnulib module netinet_in

## begin gnulib module readline


EXTRA_DIST += readline.c readline.h

EXTRA_libgnu_la_SOURCES += readline.c

## end   gnulib module readline

## begin gnulib module stdbool

BUILT_SOURCES += $(STDBOOL_H)

# We need the following in order to create <stdbool.h> when the system
# doesn't have one that works.
stdbool.h: stdbool_.h
	rm -f $@-t $@
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's/@''HAVE__BOOL''@/$(HAVE__BOOL)/g' < $(srcdir)/stdbool_.h; \
	} > $@-t
	mv $@-t $@
MOSTLYCLEANFILES += stdbool.h stdbool.h-t

EXTRA_DIST += stdbool_.h

## end   gnulib module stdbool

## begin gnulib module strdup


EXTRA_DIST += strdup.c strdup.h

EXTRA_libgnu_la_SOURCES += strdup.c

## end   gnulib module strdup

## begin gnulib module sys_socket

BUILT_SOURCES += $(SYS_SOCKET_H)

# We need the following in order to create <sys/socket.h> when the system
# doesn't have one that works with the given compiler.
sys/socket.h: socket_.h
	test -d sys || mkdir sys
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/socket_.h; \
	} > $@-t
	mv -f $@-t $@
MOSTLYCLEANFILES += sys/socket.h sys/socket.h-t
MOSTLYCLEANDIRS += sys

EXTRA_DIST += socket_.h

## end   gnulib module sys_socket

## begin gnulib module dummy

libgnu_la_SOURCES += dummy.c

## end   gnulib module dummy


mostlyclean-local: mostlyclean-generic
	@for dir in '' $(MOSTLYCLEANDIRS); do \
	  if test -n "$$dir" && test -d $$dir; then \
	    echo "rmdir $$dir"; rmdir $$dir; \
	  fi; \
	done
