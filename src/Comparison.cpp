#include <string>
#include <fstream>
#include <iostream>
#include "Comparison.hpp"
#include <bits/stdc++.h>

using namespace vdiff;

Comparison::Comparison(vdiff::Genome *gen1, vdiff::Genome *gen2)
{
    genome1 = *gen1;
    genome2 = *gen2;
}

Comparison::~Comparison() {}

void Comparison::compare_suffix_tree()
{
    std::string gen1 = genome1.get_body();
    std::string gen2 = genome2.get_body();

    SuffixTree tree1 = build_suffix_tree(gen1);
    SuffixTree tree2 = build_suffix_tree(gen2);

    std::vector<SuffixNode> nodes_tree1 = tree1.get_nodes();
    std::vector<SuffixNode> nodes_tree2 = tree2.get_nodes();

    // Remove first 2 elements from vectors: emptry string, and entire string
    nodes_tree1.erase(nodes_tree1.begin());
    nodes_tree1.erase(nodes_tree1.begin());
    nodes_tree2.erase(nodes_tree2.begin());
    nodes_tree2.erase(nodes_tree2.begin());

    for (std::vector<SuffixNode>::iterator it = nodes_tree1.begin(); it != nodes_tree1.end(); ++it)
    {
        std::cout << it->get_sub() << std::endl;
    }
    
}

SuffixTree Comparison::build_suffix_tree(std::string genome)
{
    return SuffixTree(genome);
}