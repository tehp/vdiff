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
    std::list<SuffixNode> remove_repeating_nodes(std::list<SuffixNode>);
    std::list<SuffixNode> remove_small_nodes(std::list<SuffixNode>, int size);

private:
    Genome genome1;
    Genome genome2;
};
} // namespace vdiff