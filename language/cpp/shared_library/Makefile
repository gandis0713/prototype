build:
	g++ -c -fpic bar.cpp
	g++ -c -fpic foo.cpp
	# ar crf libfoobar.a foo.o bar.o
	g++ -shared foo.o bar.o -o libfoobar.so
	gcc main.cpp libfoobar.so -g -o main.out

