#include <functional>
#include <iostream>
#include <list>
#include <vector>

namespace vdiff
{
class SuffixNode
{
public:
    SuffixNode(const std::string &sub, std::initializer_list<int> children);
    SuffixNode();
    ~SuffixNode();
    std::string sub;
    std::vector<int> ch;
    std::string get_sub();
    bool operator<(const SuffixNode &node) const;

private:
};

} // namespace vdiff