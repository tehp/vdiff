CC = g++-9
CCFLAGS = -o vdiff -Wall

main: comparison genome suffixnode suffixtree
	$(CC) -c src/main.cpp && $(CC) *.o $(CCFLAGS) && mv vdiff dist/vdiff

test: main
	./dist/vdiff

genome: 
	$(CC) -c src/genome.cpp

comparison:
	$(CC) -c src/comparison.cpp

suffixtree:
	$(CC) -c src/suffixtree.cpp

suffixnode:
	$(CC) -c src/suffixnode.cpp

clean:
	rm -rf *.o && rm dist/vdiff