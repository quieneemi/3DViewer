# @author    quieneemi

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# NAME       project name
# VERSION    build version
#
# OS         operating system
# FILES      all .cc .h files
#
# OBJ_DIR    installation path
# OBJ_NAME   executable file name
#
# QMAKE      build system executable

NAME         := 3DViewer
VERSION      := 2.0

OS           := $(shell uname -s)
FILES        := $(shell find main -regex '.*\(cc\|h\)' -not -path "*shared*")

OBJ_DIR      := build
ifeq ($(OS), Darwin)
OBJ_NAME     := $(NAME).app
else
OBJ_NAME     := $(NAME)
endif

ifeq ($(OS), Darwin)
QMAKE        := qmake
else
QMAKE        := qmake6
endif

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all        install and run program
# install
# uninstall
# clean      remove garbage
# dvi
# dist
# test       run unit tests
# linter     run code style check
# cppcheck   run static code analys

all: install
ifeq ($(OS), Darwin)
	cd $(OBJ_DIR); open $(OBJ_NAME)
else
	cd $(OBJ_DIR); ./$(OBJ_NAME)
endif

install: clean
	mkdir -p tmp
	cp -r main/* tmp
	cd tmp; $(QMAKE)
	cd tmp; make
	mkdir -p $(OBJ_DIR)
	cp -r tmp/$(OBJ_NAME) $(OBJ_DIR)
	rm -rf tmp

uninstall:
	rm -v $(OBJ_DIR)/$(OBJ_NAME)

clean:
	rm -rfv tmp logs \
	*.tar.gz *.aux *.log *.dvi *.out *.toc

dvi:
	latex docs.tex docs.dvi

dist: build dvi
	tar -czvf $(NAME)-$(VERSION).tar.gz \
	main/* build/* docs.dvi Makefile

test: clean
	mkdir -p tmp
	cp -r tests/* tmp
	cd tmp; $(QMAKE)
	cd tmp; make
	tmp/tests
	rm -rf tmp

linter:
	clang-format -n -style=google $(FILES)

cppcheck:
	cppcheck --language=c++ --std=c++17 \
	--enable=all \
	--suppress=unusedFunction \
	--suppress=missingInclude \
	$(FILES)

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: install uninstall clean dvi dist test linter cppcheck
.SILENT: