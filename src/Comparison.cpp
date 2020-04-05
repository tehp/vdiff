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

    // Try speeding things up by removing strings of length < 10
    std::cout << "Trimming genome1" << std::endl;
    nodes_tree1 = remove_small_nodes(nodes_tree1, 10);
    std::cout << "Trimming genome2" << std::endl;
    nodes_tree2 = remove_small_nodes(nodes_tree2, 10);

    // Sort to make repeats easy to remove
    std::cout << "Sorting genome1" << std::endl;
    sort(nodes_tree1.begin(), nodes_tree1.end());
    std::cout << "Sorting genome2" << std::endl;
    sort(nodes_tree2.begin(), nodes_tree2.end());

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

    // Combind similarities from the two genomes
}

std::vector<SuffixNode> Comparison::remove_small_nodes(std::vector<SuffixNode> vec, int size)
{
    int i = vec.size();
    int total = vec.size();

    // don't delete end 
    auto end = vec.end();
    advance(end, -1);
    for (std::vector<SuffixNode>::iterator it = vec.begin(); it != end; ++it)
    {
        std::cout << "trimmming... " << i-- << "/" << total << std::endl;
        if (it->get_sub().length() < size)
        {
            vec.erase(it);
        }
    }
    return vec;
}

std::vector<SuffixNode> Comparison::remove_repeating_nodes(std::vector<SuffixNode> vec)
{
    int progress = vec.size();
    for (std::vector<SuffixNode>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << progress-- << std::endl;
        auto it2 = it;
        advance(it2, 1);
        // std::cout << it->get_sub() << " / " << it2->get_sub() << std::endl;
        if (it->get_sub() == it2->get_sub())
        {
            // found match, remove all other occurances with same text as it
            std::string match_string = it->get_sub();
            while (it2->get_sub() == match_string && it2 != vec.end())
            {
                std::cout << "stuck looking at matches: " << progress << std::endl;
                progress--;
                vec.erase(it2);
                it2 = it;
                advance(it2, 1);
            }

            // remove original (last occurance remaining) of it
            auto it_delete = it;
            advance(it, -1);
            vec.erase(it_delete);
        }
    }
    return vec;
}

SuffixTree Comparison::build_suffix_tree(std::string genome)
{
    return SuffixTree(genome);
}