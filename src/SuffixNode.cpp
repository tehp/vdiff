#include <initializer_list>
#include <functional>
#include <iostream>
#include <list>
#include "SuffixNode.hpp"

using namespace vdiff;

SuffixNode::SuffixNode() {}

SuffixNode::~SuffixNode() {}

SuffixNode::SuffixNode(const std::string& sub, std::initializer_list<int> children) : sub(sub)
{
	ch.insert(ch.end(), children);
}

 SuffixNode::SuffixNode(const std::string &_sub, std::initializer_list<int> children, const std::string &_label)
 {
     sub = _sub;
     label = _label;
     ch.insert(ch.end(), children);
 }

std::string SuffixNode::get_sub()
{
	return sub;
}

 std::string SuffixNode::get_label()
 {
     return label;
 }

bool SuffixNode::operator<(const SuffixNode& node) const
{
	return sub < node.sub;
}