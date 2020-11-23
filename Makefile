CC = c++
CCFLAGS = -o vdiff -Wall
CCFLAGS_O = -std=c++17 -Wall

all: comparison genome suffixnode suffixtree placement
	$(CC) -c src/main.cpp && $(CC) *.o $(CCFLAGS) $(CCFLAGS_O) && mv vdiff dist/vdiff

test: main
	./dist/vdiff

genome: 
	$(CC) -c src/Genome.cpp $(CCFLAGS_O)

comparison:
	$(CC) -c src/Comparison.cpp $(CCFLAGS_O)

suffixtree:
	$(CC) -c src/SuffixTree.cpp $(CCFLAGS_O)

suffixnode:
	$(CC) -c src/SuffixNode.cpp $(CCFLAGS_O)

placement: 
	$(CC) -c src/Placement.cpp $(CCFLAGS_O)
	
clean:
	rm -rf *.o && rm dist/vdiff