#
#
# Makefile for dxflib
#
#

#
# dxflib installation directories
#
LIBDIR = /usr/local/lib
INCDIR = /usr/local/include/dxflib

#PREFIX ?= /usr

#LIBDIR = $(DESTDIR)$(PREFIX)/lib
#INCDIR = $(DESTDIR)$(PREFIX)/include/dxflib


#LIBDIR = $(HOME)/local/lib
#INCDIR = $(HOME)/local/include/dxflib

#
#------------------------ do not edit ------------------------
#
SHELL = /bin/sh

CC           = gcc
CXX          = g++
CFLAGS       = -I./src -g -O2  -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DLINUX=1 -DX_DISPLAY_MISSING=1 -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1
INSTALL      = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
FIND         = find
MAKEDEPEND   = :
AR           = ar
ARFLAGS      = -rs

BASE_DIR = ./src

BASE_SRC = \
		$(BASE_DIR)/dl_dxf.cpp \
		$(BASE_DIR)/dl_writer_ascii.cpp

BASE_INS = \
		$(BASE_DIR)/dl_attributes.h \
		$(BASE_DIR)/dl_codes.h \
		$(BASE_DIR)/dl_creationadapter.h \
		$(BASE_DIR)/dl_creationinterface.h \
		$(BASE_DIR)/dl_dxf.h \
		$(BASE_DIR)/dl_entities.h \
		$(BASE_DIR)/dl_exception.h \
		$(BASE_DIR)/dl_extrusion.h \
		$(BASE_DIR)/dl_writer.h \
		$(BASE_DIR)/dl_writer_ascii.h

SRC = $(BASE_SRC)
OBJ = $(SRC:.cpp=.o)

INS =  $(BASE_INS)

.cpp.o:  
	$(CXX) $(CFLAGS) -c $< -o $@


all: ./lib/libdxflib.a

./lib/libdxflib.a: $(OBJ) 
	test -d ./lib || mkdir ./lib
	$(AR) $(ARFLAGS) ./lib/libdxflib.a $(OBJ)

install: ./lib/libdxflib.a
	test -d $(LIBDIR) || mkdir -p $(LIBDIR)
	test -d $(INCDIR) || mkdir -p $(INCDIR)
	$(INSTALL_DATA) ./lib/libdxflib.a $(LIBDIR)
	#-(ln -s $(LIBDIR)/libdxflib.a $(LIBDIR)/libdxflib.a)
	for IFILE in $(INS); do \
		$(INSTALL_DATA) $$IFILE  $(INCDIR); \
	done

clean:
	-(cd ./test ; make clean)
	-rm -f $(OBJ)
	-rm -f ./lib/lib* Makefile.bak
	-rm -f ./include/dxflib/*.h
	-$(FIND) . -name "*~" -exec rm -f {} \;
	-rm -f ./lib/libdxflib.a
  
distclean: clean
	-rm -f Makefile configure

testing:	./lib/libdxflib.a
	(cd ./test ; make)

docu:
	-(doxygen ./doxygen.cfg)

dist:	clean docu
	#-rm -r ./doc/classref/html/en/*
	-rm -r ./distribution/dxflib/*
	test -d ./distribution/dxflib || mkdir -p ./distribution/dxflib
	mkdir -p ./distribution/dxflib/doc
	-(cp -r ./src ./test ./distribution/dxflib/)
	-(cp -r ./doc/classref ./distribution/dxflib/doc/)
	-(cp * ./distribution/dxflib/)
	-(cd ./distribution/dxflib; rm config.log config.cache reinstall*; mkdir lib include)
	-(cd ./distribution; tar fvcz dxflib.tar.gz dxflib)

depend:
	$(MAKEDEPEND) -- $(CFLAGS) -- $(SRC)
	@echo
	@echo "Run 'make' to build dxflib library."
	@echo

# DO NOT DELETE THIS LINE -- make  depend  depends  on it.
