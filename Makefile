CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
CHECK_FLAGS = $(shell pkg-config --libs check)
GCOV_FLAGS = --coverage

LIB_SRC_FILES = smart_calc.c
LIB_OBJ_FILES = smart_calc.o
TEST_C = test.c

.PHONY: all clean test smart_calc gcov_report

all: clean test smart_calc gcov_report

$(LIB_OBJ_FILES): $(LIB_SRC_FILES)
	$(CC) $(CFLAGS) -c $^

smart_calc.a: $(LIB_OBJ_FILES)
	ar rcs $@ $^

test: smart_calc.a $(TEST_C)
	$(CC) $(CFLAGS) $(TEST_C) -o $@ $(CHECK_FLAGS) -L. smart_calc.a -lm

gcov_report:  $(TEST_C) $(LIB_SRC_FILES)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c smart_calc.c -o smart_calc_gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_C) smart_calc_gcov.o -o $@ $(CHECK_FLAGS) -lm
	./gcov_report
	gcov -a $(TEST_C)
	gcov -a smart_calc_gcov.o
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	open coverage_html/index.html

install:
	make clean
	mkdir build
	cd build/ && qmake ../SmartCalc.pro && make
	open build/SmartCalc.app

uninstall:
	-rm -rf build*

dvi:
	#open ../README.md

dist: clean
	mkdir SmartCalc
	cp -r *.c *.h *.cpp *.ui *.pro Makefile SmartCalc
	tar -cvzf dist.tar.gz SmartCalc
	-rm -rf SmartCalc

cpp_check:
	cppcheck smart_calc.c test.c

valgrind:
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./test

clean:
	rm -f $(LIBRARY) $(LIB_OBJ_FILES) test *.out *.gch *.gcov *.gcda *.gcno *.o *.a coverage.info gcov_report test
	clang-format -i *.c *.h --style=Google
