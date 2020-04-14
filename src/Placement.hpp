#include <iostream>
#include <string.h>

namespace vdiff
{
class Placement
{
public:
    Placement(std::string string, Genome A, Genome B);
    ~Placement();
    void print_info();
    std::string get_string();
    bool operator<(const Placement& p) const;

private:
    std::string string;
    size_t start_A;
    size_t end_A;
    size_t start_B;
    size_t end_B;
    size_t length;
};
} // namespace vdiff