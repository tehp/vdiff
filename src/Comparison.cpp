#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "Comparison.hpp"

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

    // // TODO: Recursively add lines of nodes, don't just add all nodes
    // SuffixTree tree1 = build_suffix_tree(gen1);
    // SuffixTree tree2 = build_suffix_tree(gen2);

    SuffixTree d = SuffixTree(gen1, gen2);

    d.visualize();

    // std::list<std::string> nodes_tree1 = tree1.get_nodes();
    // std::list<std::string> nodes_tree2 = tree2.get_nodes();

    // Remove first 2 elements from lists: emptry string, and entire string
    // nodes_tree1.erase(nodes_tree1.begin());
    // nodes_tree1.erase(nodes_tree1.begin());
    // nodes_tree2.erase(nodes_tree2.begin());
    // nodes_tree2.erase(nodes_tree2.begin());

    // Removing strings of length < 10
    // std::cout << "Trimming genome1" << std::endl;
    // nodes_tree1 = remove_small_nodes(nodes_tree1, 10);
    // std::cout << "Trimming genome2" << std::endl;
    // nodes_tree2 = remove_small_nodes(nodes_tree2, 10);

    // Sort to make repeats easy to remove
    // std::cout << "Sorting genome1" << std::endl;
    // nodes_tree1.sort();
    // std::cout << "Sorting genome2" << std::endl;
    // nodes_tree2.sort();

    // Unique Matches:
    // Sequences in genome 1 and 2 that:
    // occur exactly once in genome1 AND exactly once in genome2
    // are not part of any larger sequence (aren't a subsequence)

    // // Remove dupes from genome1
    // std::cout << "Removing dupes genome1" << std::endl;
    // // nodes_tree1 = remove_repeating_nodes(nodes_tree1);

    // //Remove dupes from genome2
    // std::cout << "Removing dupes genome2" << std::endl;
    // // nodes_tree2 = remove_repeating_nodes(nodes_tree2);

    // // Nodes that occur in both 1 and 2
    // std::map<std::string, int> strings;
    // std::list<std::string> strings_shared;

    // for (std::list<std::string>::iterator it = nodes_tree1.begin(); it != nodes_tree1.end(); ++it)
    // {
    //     strings[*it] = 1;
    // }

    // for (std::list<std::string>::iterator it = nodes_tree2.begin(); it != nodes_tree2.end(); ++it)
    // {
    //     if (strings[*it] == 1)
    //     {
    //         strings_shared.push_back(*it);
    //         std::cout << " [" << *it << "] ";
    //     }
    // }

    // std::cout << "\nnum genome1 strings:" << nodes_tree1.size() << std::endl;
    // std::cout << "num genome2 strings:" << nodes_tree2.size() << std::endl;
    // std::cout << "num shared strings: " << strings_shared.size() << std::endl;

    // Remove strings that are substrings of another string
    // nodes_tree1 = remove_substrings(nodes_tree1);
    // nodes_tree2 = remove_substrings(nodes_tree2);
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

std::list<std::string> Comparison::remove_repeating_nodes(std::list<std::string> list)
{
    std::string last = "";
    for (std::list<std::string>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (*it == last)
        {
            list.erase(it);
        }
        else
        {
            last = *it;
            it = next(it);
        }
    }
    return list;
}

std::list<SuffixNode> Comparison::remove_substrings(std::list<SuffixNode> list)
{
    std::list<SuffixNode> original = list;
    std::list<SuffixNode>::iterator it = list.begin();

    while (it != list.end())
    {
        if (check_if_substring(it->get_sub(), original))
        {
            auto delete_it = it;
            it = next(it);
            list.erase(delete_it);
        }
        else
        {
            it = next(it);
        }
        std::cout << list.size() << std::endl;
    }
    return list;
}

int Comparison::check_if_substring(std::string str, std::list<SuffixNode> list)
{
    for (std::list<SuffixNode>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (it->get_sub().length() > str.length())
        {
            if (it->get_sub() != str && it->get_sub().find(str) != std::string::npos)
            {
                return 1;
            }
        }
    }
    return 0;
}

// SuffixTree Comparison::build_suffix_tree(std::string genome)
// {
//     // SuffixTree(genome).visualize();
//     return SuffixTree(genome);
// }
