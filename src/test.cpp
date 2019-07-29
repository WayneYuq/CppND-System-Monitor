#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
using std::cout;

int main(int argc, char const *argv[])
{
    // Using sysconf to get clock ticks of the host machine
    cout << sysconf(_SC_CLK_TCK) << "\n";
    std::ifstream stream("/home/sun/working_projects/服务器登录");
    std::string line;
    while (std::getline(stream, line))
    {
        cout << line << "\n";
        std::istringstream buf(line);
        std::istream_iterator<std::string> beg(buf), end;
        // cout << beg << "\n";
        std::vector<std::string> values(beg, end);
        for (int i = 0; i < values.size(); i++)
        {
            cout << values[i] << "\n";
        }
        
    }
    return 0;
}
