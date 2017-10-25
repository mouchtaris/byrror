SHELL = /bin/bash

SRCDIR = $(shell pwd)
BUILDDIR = /tmp/bb

all:
	cmake --build "${BUILDDIR}"
	ln -svf "${BUILDDIR}/compile_commands.json" ./
	# bundler exec ruby add_headers_to_compile_commands.rb

defs:
	rm -rfv "${BUILDDIR}"
	mkdir -pv "${BUILDDIR}"
	bash -x -c 'cd ${BUILDDIR} && cmake -G Ninja ${SRCDIR}'

cclean:
	rm -rfv CMakeCache.txt
	rm -rfv CMakeFiles/
	rm -rfv Makefile
	rm -rfv cmake_install.cmake

run: all
	/tmp/bb/byrror
