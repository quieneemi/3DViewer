OS = $(shell uname -s)
INSTALLATION_PATH = ~/

all: install run

install: build
	cp build/3DViewer $(INSTALLATION_PATH)

uninstall:
	rm $(INSTALLATION_PATH)3DViewer

clean:
	rm -rfv *.tar.gz docs.aux docs.log docs.dvi docs.toc build tests-build

dvi:
	latex docs.texi docs.dvi
	open docs.dvi

dist: build
	tar -czvf 3DViewer-2.0.tar.gz build/3DViewer

tests: build_tests
ifeq ($(OS), Darwin)
	cd tests-build; open Tests.app
else
	cd tests-build; ./Tests
endif

run:
ifeq ($(OS), Darwin)
	cd $(INSTALLATION_PATH); open 3DViewer.app
else
	cd $(INSTALLATION_PATH); ./3DViewer
endif

build:	clean
	mkdir -p build
	cp -r main/* build/
ifeq ($(OS), Linux)
	cd build; qmake6
else
	cd build; qmake
endif
	cd build; make

build_tests: clean
	mkdir -p tests-build
	cp -r tests/* tests-build/
ifeq ($(OS), Linux)
	cd tests-build; qmake6
else
	cd tests-build; qmake
endif
	cd tests-build; make

cppcheck:
	cppcheck --language=c++ --std=c++17 \
	--enable=all \
	--suppress=unusedFunction \
	--suppress=missingInclude \
	main/*.cc main/*.h

linter:
	clang-format -n -style=google \
	main/*.cc main/*.h tests/main.cc

check: cppcheck linter leaks
