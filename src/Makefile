CC = gcc
#--------------------------------------------------------------------------------------------
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror
#--------------------------------------------------------------------------------------------
TEST_FLAGS = -lcheck
TESTS = test
#--------------------------------------------------------------------------------------------
REPORT = gcov_report
GCOV_REPORT = gcov/$(REPORT)
GCOV_INFO = $(GCOV_REPORT).info
GCOV_FLAGS  = --coverage -lcheck
#--------------------------------------------------------------------------------------------
OS = $(shell uname)
3DVIEWER = OpenGL_1.app
#--------------------------------------------------------------------------------------------
ifeq ($(OS), Linux)
	TEST_FLAGS += -lm -lsubunit -D_GNU_SOURCE -lrt
	GCOV_FLAGS += -lrt -lsubunit -lpthread -lm
	SMARTCALC = smartcalc
endif
#--------------------------------------------------------------------------------------------

.PHONY: all install dvi dist test gcov_report uninstall clean

all: install test gcov_report

test: clean
	$(CC) $(CFLAGS) ./back/$(TESTS).c ./back/s21_parcer.c $(TEST_FLAGS) -o $(TESTS)
	./$(TESTS)

$(REPORT): clean
	mkdir -p gcov
	gcc $(CFLAGS) ./back/s21_parcer.c ./back/$(TESTS).c $(GCOV_FLAGS) -o $(GCOV_REPORT) -DUNIT_TESTING -ggdb3 -fPIC -O0 --coverage
	./$(GCOV_REPORT)
ifeq ($(OS), Darwin)
	mv *.gcno *.gcda gcov
endif
	lcov -t "$(REPORT)" -o $(GCOV_INFO) -c -d gcov
	genhtml -o report $(GCOV_INFO) $(GCOV_INFO)
	open report/index.html

install: uninstall clean
	mkdir build
	cd front && qmake && make && make clean && rm Makefile && cd ../ && mv front/OpenGL_1.app build/


check_leaks:
	make clean
	make install
	CK_FORK=no leaks --atExit -- ./build/OpenGL_1.app/Contents/MacOS/OpenGL_1 > logfile.log

dvi:
	open dvi/index.html

dist: install
	rm -rf ../Archive_3DViewer/
	mkdir ../Archive_3DViewer/
	cp -a **/ ./* Makefile ./build/$(3DVIEWER) ../Archive_3DViewer
	cd ../ && tar -cvzf Archive_3DViewer.tar.gz Archive_3DViewer

uninstall:
	rm -rf ./build*

clean:
	rm -rf *.{a,o,dSYM,out}
	rm -rf gcov_report
	rm -rf report
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf Tests/test
	rm -rf ../*.gz
	rm -rf ../Archive_3DViewer
	rm -rf gcov
	rm -rf test
	rm -rf RESULT.txt
	rm -rf ../src/3DViewer/*.o
	rm -rf build
	rm -rf *.log

style:
	echo "======= CHECK GOOGLE CODE STYLE ======="
	sleep 1
	clang-format -n ./front/*.cpp ./front/*.h ./back/*.c ./back/*.h