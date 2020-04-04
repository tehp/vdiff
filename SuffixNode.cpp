#include <functional>
#include <iostream>
#include <vector>
#include "SuffixNode.hpp"

using namespace vdiff;

SuffixNode::SuffixNode() {}

SuffixNode::~SuffixNode() {}

SuffixNode::SuffixNode(const std::string &sub, std::initializer_list<int> children) : sub(sub)
{
    ch.insert(ch.end(), children);
}

std::string SuffixNode::get_sub() {
    return sub;
}