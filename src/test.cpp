#include <iostream>
#include <unistd.h>
#include <vector>
using std::cout;
using namespace std;

int main(int argc, char const *argv[])
{
    cout << "sdfsdf: " << "\n";
    // Using sysconf to get clock ticks of the host machine
    /**
     * 
     * 
     * process up time
     * clock ticks
     * freq = sysconf(_SC_CLK_TCK);
     * istringstream buf(line);
     * std::istream_iterator<string> beg(buf), end;
     * std::vector<string> values(beg, end);
     * 
     *
     * 
     */
    cout << sysconf(_SC_CLK_TCK) << "\n";
    (vector<string>());
    return 0;
}
