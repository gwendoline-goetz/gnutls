# Copyright (C) 2004-2007 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the specification of how gnulib-tool is used.
# It acts as a cache: It is written and read by gnulib-tool.
# In projects using CVS, this file is meant to be stored in CVS,
# like the configure.ac and various Makefile.am files.


# Specification in the form of a command-line invocation:
#   gnulib-tool --import --dir=. --local-dir=gl/override --lib=libgnu --source-base=gl --m4-base=gl/m4 --doc-base=doc --aux-dir=. --avoid=snprintf --avoid=vasnprintf --makefile-name=gnulib.mk --libtool --macro-prefix=gl arpa_inet fdl gendocs getaddrinfo getline getpass gpl inet_ntop inet_pton lgpl maintainer-makefile readline

# Specification in the form of a few gnulib-tool.m4 macro invocations:
gl_LOCAL_DIR([gl/override])
gl_MODULES([arpa_inet fdl gendocs getaddrinfo getline getpass gpl inet_ntop inet_pton lgpl maintainer-makefile readline])
gl_AVOID([snprintf vasnprintf])
gl_SOURCE_BASE([gl])
gl_M4_BASE([gl/m4])
gl_DOC_BASE([doc])
gl_TESTS_BASE([gl/tests])
gl_LIB([libgnu])
gl_MAKEFILE_NAME([gnulib.mk])
gl_LIBTOOL
gl_MACRO_PREFIX([gl])
