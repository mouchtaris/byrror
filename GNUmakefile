SHELL = /bin/bash

SRCDIR = $(shell pwd)
BUILDDIR = /tmp/bb

all:
	cmake --build "${BUILDDIR}"
	ln -svf "${BUILDDIR}/compile_commands.json" ./

defs:
	rm -rfv "${BUILDDIR}"
	mkdir -pv "${BUILDDIR}"
	bash -x -c 'cd ${BUILDDIR} && cmake ${SRCDIR}'

cclean:
	rm -rfv CMakeCache.txt
	rm -rfv CMakeFiles/
	rm -rfv Makefile
	rm -rfv cmake_install.cmake
