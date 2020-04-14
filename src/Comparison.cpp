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
    matches = remove_small_nodes(matches, 800);

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

    // Remove strings that are substrings of another string
    std::cout << "finding and removing matches that are substrings of other matches" << std::endl;
    matches = remove_substrings(matches);
    std::cout << "number of matches after removing substrings: " << matches.size() << std::endl;

    std::string largest = "";
    for (std::list<std::string>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        if (it->length() > largest.length())
        {
            largest = *it;
        }
    }

    create_placements(matches);

    placements.sort();

    // std::cout << largest << std::endl;
}

int Comparison::create_placements(std::list<std::string> matches)
{
    for (std::list<std::string>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        Placement p = Placement(*it, genome1, genome2);
        p.print_info();
        placements.push_back(p);
    }

    return 1;
}

std::list<std::string> Comparison::remove_small_nodes(std::list<std::string> list, size_t size)
{
    for (std::list<std::string>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::string str = *it;
        if (str.length() < size)
        {
            it = list.erase(it);
            std::advance(it, -1);
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

std::list<std::string> Comparison::remove_substrings(std::list<std::string> list)
{
    std::list<std::string> original = list;
    std::list<std::string>::iterator it = list.begin();

    int total = list.size();
    int count = 1;

    std::cout << "removing substrings" << std::endl;

    while (it != list.end())
    {
        if (check_if_substring(*it, original))
        {
            auto delete_it = it;
            it = next(it);
            list.erase(delete_it);
        }
        else
        {
            it = next(it);
        }
        std::cout << "\e[A";
        std::cout << "removing substrings [" << count++ << "/" << total << "]" << std::endl;
    }
    return list;
}

int Comparison::check_if_substring(std::string str, std::list<std::string> list)
{
    for (std::list<std::string>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (it->length() > str.length())
        {
            if (*it != str && it->find(str) != std::string::npos)
            {
                return 1;
            }
        }
    }
    return 0;
}