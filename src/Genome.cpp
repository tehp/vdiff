#include "Genome.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace vdiff;

Genome::Genome(std::string _name)
{
    name = _name;
}

Genome::Genome()
{
    name = "";
    body = "";
    len = 0;
    adenine_count = 0;
    cytosine_count = 0;
    guanine_count = 0;
    thymine_count = 0;
}

int Genome::get_len() {
    return len;
}

Genome::~Genome() {

}

int Genome::read_file(std::string path)
{
    std::ifstream file(path);
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            body.append(line);
        }
    }
    else
    {
        return 0;
    }

    len = body.length();

    adenine_count = std::count(body.begin(), body.end(), 'A');
    cytosine_count = std::count(body.begin(), body.end(), 'C');
    guanine_count = std::count(body.begin(), body.end(), 'G');
    thymine_count = std::count(body.begin(), body.end(), 'T');

    file.close();
    return 1;
}

std::string Genome::get_body()
{
    return body;
}

void Genome::print_info()
{
    std::cout << "read genome: " << name << ", length: " << len << std::endl;
    std::cout << "A: " << adenine_count << ", C: " << cytosine_count << ", G: " << guanine_count << ", T: " << thymine_count << std::endl;
}