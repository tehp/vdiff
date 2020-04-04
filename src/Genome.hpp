#include <iostream>
#include <string.h>

namespace vdiff
{
class Genome
{
public:
    Genome(std::string name);
    Genome();
    ~Genome();
    int read_file(std::string path);
    std::string get_body();
    int get_len();
    void print_info();

private:
    std::string name;
    std::string body;
    int len;
    int adenine_count;
    int cytosine_count;
    int guanine_count;
    int thymine_count;
};
} // namespace vdiff