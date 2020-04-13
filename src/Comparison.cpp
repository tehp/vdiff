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

    SuffixTree tree = SuffixTree(gen1, gen2);

    std::list<std::string> matches = tree.get_all_matches();

    std::cout << "number of matches: " << matches.size() << std::endl;

    //tree.visualize();

    // Removing strings of length < 10
    std::cout << "trimming matches..." << std::endl;
    matches = remove_small_nodes(matches, 10);

    std::cout << "number of matches after trim: " << matches.size() << std::endl;

    // Sort to make repeats easy to remove
    std::cout << "sorting matches" << std::endl;
    matches.sort();

    // Unique Matches:
    // Sequences in genome 1 and 2 that:
    // occur exactly once in genome1 AND exactly once in genome2
    // are not part of any larger sequence (aren't a subsequence)

    // Remove dupes from matches
    std::cout << "removing dupe matches" << std::endl;
    matches = remove_repeating_nodes(matches);

    std::cout << "number of matches after dupes removed: " << matches.size() << std::endl;

    // // Nodes that occur in both 1 and 2
    // std::map<std::string, int> strings;
    // std::list<std::string> strings_shared;

    // for (std::list<std::string>::iterator it = matches.begin(); it != matches.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
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

std::list<std::string> Comparison::remove_small_nodes(std::list<std::string> list, size_t size)
{
    for (std::list<std::string>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::string str = *it;
        if (str.length() < size)
        {
            it = list.erase(it);
            if (it != list.begin())
            {
                std::advance(it, -1);
            }
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
            it = list.erase(it);
        }
        else
        {
            last = *it;
            if (next(it) != list.end())
            {
                it = next(it);
            }
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
