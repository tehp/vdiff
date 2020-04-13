#include <initializer_list>
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
    SuffixNode(const std::string &sub, std::initializer_list<int> children, const std::string &label);
    SuffixNode();
    ~SuffixNode();
    std::string sub;
    std::vector<int> ch;
    std::string get_sub();
    std::string get_label();
    bool operator<(const SuffixNode &node) const;

private:
    std::string label;
};

} // namespace vdiff