#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include "SuffixNode.hpp"

namespace vdiff
{

class SuffixTree
{
public:
    SuffixTree(const std::string &A, const std::string &B);
    void visualize();
    std::list<std::string> get_leafs();
    std::list<std::string> get_all_matches();

private:
    std::vector<SuffixNode> nodes;
    void addSuffix(const std::string &suf, const std::string &label);
};
} // namespace vdiff
