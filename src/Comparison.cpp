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

    std::vector<SuffixNode> nodes_tree1_vector = tree1.get_nodes();
    std::vector<SuffixNode> nodes_tree2_vector = tree2.get_nodes();

    std::list<SuffixNode> nodes_tree1;
    std::list<SuffixNode> nodes_tree2;

    std::copy(nodes_tree1_vector.begin(), nodes_tree1_vector.end(), std::back_inserter(nodes_tree1));
    std::copy(nodes_tree2_vector.begin(), nodes_tree2_vector.end(), std::back_inserter(nodes_tree2));

    // Remove first 2 elements from lists: emptry string, and entire string
    nodes_tree1.erase(nodes_tree1.begin());
    nodes_tree1.erase(nodes_tree1.begin());
    nodes_tree2.erase(nodes_tree2.begin());
    nodes_tree2.erase(nodes_tree2.begin());

    // Try speeding things up by removing strings of length < 10
    std::cout << "Trimming genome1" << std::endl;
    nodes_tree1 = remove_small_nodes(nodes_tree1, 10);
    std::cout << "Trimming genome2" << std::endl;
    nodes_tree2 = remove_small_nodes(nodes_tree2, 10);

    // Sort to make repeats easy to remove
    std::cout << "Sorting genome1" << std::endl;
    nodes_tree1.sort();
    std::cout << "Sorting genome2" << std::endl;
    nodes_tree2.sort();

    // Unique Matches:
    // Sequences in genome 1 and 2 that:
    // occur exactly once in genome1 AND exactly once in genome2
    // are not part of any larger sequence (aren't a subsequence)

    // Remove dupes from genome1
    std::cout << "Removing dupes genome1" << std::endl;
    nodes_tree1 = remove_repeating_nodes(nodes_tree1);

    // Remove dupes from genome2
    std::cout << "Removing dupes genome2" << std::endl;
    nodes_tree2 = remove_repeating_nodes(nodes_tree2);

    // Remove strings that are substrings of another string

    // Combine similarities from the two genomes
}

std::list<SuffixNode> Comparison::remove_small_nodes(std::list<SuffixNode> list, int size)
{
    int i = list.size();
    int total = list.size();

    // don't delete end
    auto end = list.end();
    advance(end, -1);
    for (std::list<SuffixNode>::iterator it = list.begin(); it != end; ++it)
    {
        if (it->get_sub().length() < size)
        {
            list.erase(it);
        }
    }
    return list;
}

std::list<SuffixNode> Comparison::remove_repeating_nodes(std::list<SuffixNode> list)
{
    std::string last = "";
    for (std::list<SuffixNode>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (it->get_sub() == last) {
            list.erase(it);
        } else {
            last = it->get_sub();
            it = next(it);
        }
    }
    return list;
}

SuffixTree Comparison::build_suffix_tree(std::string genome)
{
    return SuffixTree(genome);
}