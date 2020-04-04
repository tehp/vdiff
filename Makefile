CC = g++-9
CCFLAGS = -o vdiff -Wall

main: comparison genome suffixnode suffixtree
	$(CC) -c main.cpp && $(CC) *.o $(CCFLAGS) && mv vdiff dist/vdiff

test: main
	./dist/vdiff

genome: 
	$(CC) -c genome.cpp

comparison:
	$(CC) -c comparison.cpp

suffixtree:
	$(CC) -c suffixtree.cpp

suffixnode:
	$(CC) -c suffixnode.cpp

clean:
	rm -rf *.o && rm dist/vdiff