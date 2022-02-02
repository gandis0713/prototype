build:
	gcc -c bar.cpp
	gcc -c foo.cpp
	ar crf libfoobar.a foo.o bar.o
	gcc main.cpp libfoobar.a -o main.out

