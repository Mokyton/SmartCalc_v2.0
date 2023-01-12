CFLAGS = -Wall -Werror -Wextra

all:
	make tests

tests:
	gcc $(CFLAGS) -lgtest -lstdc++ -std=c++17 Model/s21_model.cc gtests/tests.cc -o test.o
	./test.o

gcov_report:
	gcc  --coverage Model/s21_model.cc gtests/tests.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html

clean:
	rm -rf *.o *.out
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report

dvi:
	@makeinfo --html --no-warn --no-validate --force ./info.texi
	@cd info; open index.html


dvi_txt:
	open info.txt


install:
	make uninstall
	mkdir build
	cd View && qmake && make && make clean && rm Makefile && cd ../ && mv View/View.app build

uninstall:
	rm -rf build

dist: install
	rm -rf Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/src
	mv ./build/View.app Archive_SmartCalc_v2.0/src/
	tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	rm -rf Archive_SmartCalc_v2.0/
	rm -rf build
