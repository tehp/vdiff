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
    matches = remove_small_nodes(matches, 500);

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

    // Optimize for longest set of MUMs that occur in the same order in A and B

    // DP approach to LIS.
    // "Most-valuable Increasing Subsequence"
    // based on length of each unique match
    std::vector<std::pair<int, int>> start_length;
    for (std::list<Placement>::iterator it = placements.begin(); it != placements.end(); ++it)
    {
        start_length.push_back(std::pair<int, int>(it->get_start_B(), it->get_length()));
    }

    std::vector<std::vector<std::pair<int, int>>> LIS = find_LIS(start_length);

    std::vector<std::pair<int, int>> best = LIS.back();

    for (auto it = placements.begin(); it != placements.end(); ++it)
    {
        int found = 0;
        for (auto it2 = best.begin(); it2 != best.end(); ++it2)
        {
            if ((int)it->get_start_B() == it2->first)
            {
                // placement is part of best placements
                found = 1;
                break;
            }
        }
        if (!found)
        {
            // placement isnt one of the best placements
            it = placements.erase(it);
            std::advance(it, -1);
        }
    }

    int count_matches = 0;

    for (std::list<Placement>::iterator it = placements.begin(); it != placements.end(); ++it)
    {
        count_matches += it->get_length();
    }

    std::cout << "# matching: " << count_matches << "/" << std::min(genome1.get_len(), genome2.get_len()) << std::endl;
    std::cout << "% matching: " << (double)count_matches / (double)std::min(genome1.get_len(), genome2.get_len()) * 100 << " between: " << genome1.get_name() << " and " << genome2.get_name() << std::endl;
}

// Takes index, size
// Optimizes for largest size, with all elements index increasing
std::vector<std::vector<std::pair<int, int>>> Comparison::find_LIS(std::vector<std::pair<int, int>> &D)
{
    std::vector<std::vector<std::pair<int, int>>> L(D.size());
    L[0].push_back(D[0]);

    for (size_t i = 1; i < D.size(); i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if ((D[j].first < D[i].first) && (L[i].size() < L[j].size() + 1))
            {
                L[i] = L[j];
            }
        }
        L[i].push_back(D[i]);
    }

    sort(L.begin(), L.end(), [](const auto &lhs, const auto &rhs) {
        int sum_l = 0;
        int sum_r = 0;

        for (auto it_l = lhs.begin(); it_l != lhs.end(); ++it_l)
        {
            sum_l += it_l->second;
        }

        for (auto it_r = rhs.begin(); it_r != rhs.end(); ++it_r)
        {
            sum_r += it_r->second;
        }

        return sum_l < sum_r;
    });

    return L;
}

int Comparison::create_placements(std::list<std::string> matches)
{
    for (std::list<std::string>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        Placement p = Placement(*it, genome1, genome2);
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