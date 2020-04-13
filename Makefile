CC = g++-9
CCFLAGS = -o vdiff -Wall
CCFLAGS_O = -std=c++17 -Wall

main: comparison genome suffixnode suffixtree
	$(CC) -c src/main.cpp && $(CC) *.o $(CCFLAGS) $(CCFLAGS_O) && mv vdiff dist/vdiff

test: main
	./dist/vdiff

genome: 
	$(CC) -c src/genome.cpp $(CCFLAGS_O)

comparison:
	$(CC) -c src/comparison.cpp $(CCFLAGS_O)

suffixtree:
	$(CC) -c src/suffixtree.cpp $(CCFLAGS_O)

suffixnode:
	$(CC) -c src/suffixnode.cpp $(CCFLAGS_O)

clean:
	rm -rf *.o && rm dist/vdiff