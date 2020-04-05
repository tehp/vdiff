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
    SuffixTree(const std::string &str);
    void visualize();
    std::vector<SuffixNode> get_nodes();

private:
    std::vector<SuffixNode> nodes;
    void addSuffix(const std::string &suf);
};
} // namespace vdiff
