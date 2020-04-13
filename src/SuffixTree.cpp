#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include "SuffixTree.hpp"

using namespace vdiff;

// DOUBLE SUFFIX TREE
SuffixTree::SuffixTree(const std::string &A, const std::string &B)
{
    nodes.push_back(SuffixNode{});
    for (size_t i = 0; i < A.length(); i++)
    {
        addSuffix(A.substr(i), "A");
    }
    for (size_t i = 0; i < B.length(); i++)
    {
        addSuffix(B.substr(i), "B");
    }
}

std::list<std::string> SuffixTree::get_all_matches()
{

    std::function<void(int, const std::string &, std::string parent)> f;

    std::list<std::string> matches;

    f = [&](int n, const std::string &pre, std::string parent) {
        auto children = nodes[n].ch;

        if (children.size() == 2)
        {
            if (nodes[nodes[n].ch[0]].get_label() != nodes[nodes[n].ch[1]].get_label())
            {
                // std::cout << "BELOW IS A MATCH: " << nodes[nodes[n].ch[0]].sub << " / " << nodes[nodes[n].ch[1]].sub << std::endl;
                matches.push_back(parent + nodes[n].sub);
            }
        }

        if (children.size() == 0)
        {
            // std::cout << "- " << nodes[n].sub << " : " << nodes[n].get_label() << "\n";
            return;
        }

        // this is not a leaf
        parent.append(nodes[n].sub);

        auto it = std::begin(children);
        if (it != std::end(children))
            do
            {
                if (std::next(it) == std::end(children))
                    break;
                f(*it, pre + "| ", parent);
                it = std::next(it);
            } while (true);

        f(children[children.size() - 1], pre + "  ", parent);
    };

    f(0, "", "");

    return matches;
}

std::list<std::string> SuffixTree::get_leafs()
{
    std::list<std::string> leafs;
    std::function<void(int, const std::string &, std::string parent)> f;

    f = [&](int n, const std::string &pre, std::string parent) {
        std::string str = "";
        auto children = nodes[n].ch;

        // if empty
        if (children.size() == 0)
        {
            // this is a leaf, add to suffix tree leafs
            leafs.push_back(parent + nodes[n].sub);
            return;
        }

        // this is not a leaf
        parent.append(nodes[n].sub);

        // iterate children
        auto it = std::begin(children);

        str.append(nodes[n].sub);

        if (it != std::end(children))
            do
            {
                if (std::next(it) == std::end(children))
                    break;
                f(*it, pre + "| ", parent);
                it = std::next(it);
            } while (true);

        f(children[children.size() - 1], pre + "  ", parent);
    };

    f(0, "", "");

    return leafs;
}

void SuffixTree::visualize()
{
    if (nodes.size() == 0)
    {
        std::cout << "<empty>\n";
        return;
    }

    std::function<void(int, const std::string &)> f;
    f = [&](int n, const std::string &pre) {
        auto children = nodes[n].ch;
        if (children.size() == 0)
        {
            std::cout << "- " << nodes[n].sub << " : " << nodes[n].get_label() << "\n";
            return;
        }
        std::cout << "+ " << nodes[n].sub << '\n';

        auto it = std::begin(children);
        if (it != std::end(children))
            do
            {
                if (std::next(it) == std::end(children))
                    break;
                std::cout << pre << "+-";
                f(*it, pre + "| ");
                it = std::next(it);
            } while (true);

        std::cout << pre << "+-";
        f(children[children.size() - 1], pre + "  ");
    };

    f(0, "");
}

void SuffixTree::addSuffix(const std::string &suf, const std::string &label)
{
    int n = 0;
    size_t i = 0;
    while (i < suf.length())
    {
        char b = suf[i];
        size_t x2 = 0;
        int n2;
        while (true)
        {
            auto children = nodes[n].ch;
            if (x2 == children.size())
            {
                // no matching child, remainder of suf becomes new node
                n2 = nodes.size();
                nodes.push_back(SuffixNode(suf.substr(i), {}, label));
                nodes[n].ch.push_back(n2);
                return;
            }
            n2 = children[x2];
            if (nodes[n2].sub[0] == b)
            {
                break;
            }
            x2++;
        }
        // find prefix of remaining suffix in common with child
        auto sub2 = nodes[n2].sub;
        size_t j = 0;
        while (j < sub2.size())
        {
            if (suf[i + j] != sub2[j])
            {
                // split n2
                auto n3 = n2;
                // new node for the part in common
                n2 = nodes.size();
                nodes.push_back(SuffixNode(sub2.substr(0, j), {n3}, label));
                nodes[n3].sub = sub2.substr(j); // old node loses the part in common
                nodes[n].ch[x2] = n2;
                break; // continue down the tree
            }
            j++;
        }
        i += j; // advance past part in common
        n = n2; // continue down the tree
    }
}