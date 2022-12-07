TESTCOVERAGE = -fprofile-arcs -ftest-coverage
CPP = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm
STD = g++ --std=c++17
WASH=rm -rf *.o *.a *.out *.log *.aux *.dvi *.toc *css *gcno *gcda CPPLINT.cfg *tgz *.html man_ru report .clang-format
OS=$(shell uname)

ifeq ($(OS), Linux)
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s
	TEST =  -lgtest -lgmock -pthread --coverage
else
	LEAKS=CK_FORK=no leaks --atExit --
	TEST =  -lgtest -fsanitize=address -lgmock -pthread --coverage
endif


all: clean test gcov_report


install: build clean


build:
	mkdir build
	cd build; cmake ..
	make -C build


uninstall:
	rm -rf $(HOME)/Desktop/Calculator/
	rm -rf build


dvi:
	makeinfo --html --no-warn --no-validate --force ./man_ru.texi


dist:
	rm -rf MyCalc
	mkdir MyCalc
	cp Makefile Model/* View/* Controller/* *.h *.txt *.texi *.cpp *.user MyCalc/
	tar -zcvf ./MyCalc.tar.tgz ./MyCalc
	rm -rf MyCalc/


read: read.o parse.o validate.o calculate.o rpn.o calculatedeposit.o
	$(STD) $^ -o read.out && ./read.out


gcov_report: test
	./test.out
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html


test: parse.o validate.o calculate.o rpn.o calculatedeposit.o
	g++ test.cpp $^ -o test.out -lgtest -lgmock -pthread --coverage 
	./test.out


test.o: test.cpp
	g++ $(STD) $(TESTCOVERAGE) -c $^ -o $@ 


read.o: Model/read.cpp
	$(STD) $(TESTCOVERAGE) -c $^


rpn.o: Model/rpn.cpp
	$(STD) $(TESTCOVERAGE) -c $^


parse.o: Model/parse.cpp
	$(STD) $(TESTCOVERAGE) -c $^


calculate.o: Model/calculate.cpp
	$(STD) $(TESTCOVERAGE) -c $^


validate.o: Model/validate.cpp
	$(STD) $(TESTCOVERAGE) -c $^


calculatedeposit.o: Model/calculatedeposit.cpp
	$(STD) $(TESTCOVERAGE) -c $^


leaks:
	$(LEAKS) ./test.out


clang:
	cp ../materials/linters/.clang-format ./
	# clang-format -i Controller/* Model/* View/*.cpp View/*.h test.cpp main.cpp
	clang-format -n Controller/* Model/* View/*.cpp View/*.h test.cpp main.cpp


cppcheck:
	-cppcheck --language=c++ --enable=all --std=c++17 Model/* Controller/* View/*.cpp *.h test.cpp $(CPP)


clean:
	$(WASH)