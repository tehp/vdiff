#include <string>
#include <iostream>
#include <cstdlib>
#include "Genome.hpp"
#include "Placement.hpp"

using namespace vdiff;

Placement::Placement(std::string _string, Genome A, Genome B)
{
    string = _string;
    length = string.length();

    if (A.get_body().find(string) != std::string::npos)
    {
        start_A = A.get_body().find(string);
        end_A = start_A + length;
    }
    else
    {
        std::cout << "error making placement, string not found in genome A.";
    }

    if (B.get_body().find(string) != std::string::npos)
    {
        start_B = B.get_body().find(string);
        end_B = start_B + length;
    }
    else
    {
        std::cout << "error making placement, string not found in genome B.";
    }
}

bool Placement::operator<(const Placement& p) const
{
	return string < p.string;
}

std::string Placement::get_string() {
    return string;
}

void Placement::print_info() {
    std::cout << "placement:\nlength: " << length << ". start_A: " << start_A << ". start_B: " << start_B << ". difference: " << abs(start_A - start_B) << std::endl;
}

Placement::~Placement() {}