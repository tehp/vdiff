#include "Comparison.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// A: Adenine
// C: Cytosine
// G: Guanine
// T: Thymine

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "Error: Incorrect Arguments\nusage: vdiff [genome1] [genome2] [min_match_size]" << std::endl;
    }
    else
    {
        std::string genome1 = argv[1];
        std::string genome2 = argv[2];

        std::istringstream ss(argv[3]);
        int min_match_size;
        ss >> min_match_size;

        vdiff::Genome g1 = vdiff::Genome(genome1);
        vdiff::Genome g2 = vdiff::Genome(genome2);

        g1.read_file("genomes/" + genome1);
        g2.read_file("genomes/" + genome2);

        g1.print_info();
        g2.print_info();

        std::cout << "min match size: " << min_match_size << std::endl;

        vdiff::Comparison comparison = vdiff::Comparison(&g1, &g2, min_match_size);

        comparison.compare_suffix_tree();
    }

    return 0;
}