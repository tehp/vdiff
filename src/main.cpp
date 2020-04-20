#include "Comparison.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// A: Adenine
// C: Cytosine
// G: Guanine
// T: Thymine

int main()
{
    vdiff::Genome cov = vdiff::Genome("sars");
    vdiff::Genome sars = vdiff::Genome("COVID19");

    cov.read_file("genomes/sars");
    sars.read_file("genomes/cov");

    cov.print_info();
    sars.print_info();

    vdiff::Comparison cov_sars = vdiff::Comparison(&cov, &sars);
    
    cov_sars.compare_suffix_tree();

    return 0;
}