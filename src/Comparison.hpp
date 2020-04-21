#include <iostream>
#include <string.h>
#include "Genome.hpp"
#include "SuffixTree.hpp"
#include "Placement.hpp"

namespace vdiff
{
class Comparison
{
public:
    Comparison(Genome *gen1, Genome *gen2, int min_match_size);
    ~Comparison();
    void compare_suffix_tree();
    SuffixTree build_suffix_tree(std::string genome);
    std::list<std::string> remove_repeating_nodes(std::list<std::string>);
    std::list<std::string> remove_small_nodes(std::list<std::string>, size_t size);
    std::list<std::string> remove_substrings(std::list<std::string>);
    int check_if_substring(std::string str, std::list<std::string>);
    int create_placements(std::list<std::string>);
    std::vector<std::vector<std::pair<int, int> > > find_LIS(std::vector<std::pair<int, int> > &D);

private:
    Genome genome1;
    Genome genome2;
    std::list<Placement> placements;
    int min_match_size;
};
} // namespace vdiff