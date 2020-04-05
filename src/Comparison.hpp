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
    std::vector<SuffixNode> remove_repeating_nodes(std::vector<SuffixNode>);
    std::vector<SuffixNode> remove_small_nodes(std::vector<SuffixNode>, int size);

private:
    Genome genome1;
    Genome genome2;
};
} // namespace vdiff