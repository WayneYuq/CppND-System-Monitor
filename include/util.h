#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <fstream>

// Classic helper functions
class Util {
    public:
        static std::string convertToTime ( long int input_seconds );
        static std::string getProgressBar(std::string percent);
        static std::ifstream getStream(std::string path);
};

#endif // UTIL_H