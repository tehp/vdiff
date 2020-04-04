#include <iostream>
#include <string.h>
#include "Genome.hpp"
#include "SuffixTree.hpp"

namespace vdiff
{
class Comparison
{
public:
    Comparison(Genome *gen1, Genome *gen2);
    ~Comparison();
    void compare_suffix_tree();
    SuffixTree build_suffix_tree(std::string genome);

private:
    Genome genome1;
    Genome genome2;
};
} // namespace vdiff