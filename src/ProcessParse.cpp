#include <fstream>

std::string ProcessParse::getVmSize(std::string pid)
{
    string line;
    string name {"VmData"};
    string value;
    float result;

    ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
    while(std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            std::vector<string> values(beg, end);
            result = (stof(values[1]) / float(1024 * 1024));
            break;
        }
    };
    return std::to_string(result);
}

std::string ProcessParse::getCpuPercent(std::string pid)
{
    std::string line;
    std::string value;
    float result;
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::statPath()));
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = stof(ProcessParse::getProcUpTime(pid));
    float stime = stof(values[14]);
    float cutime = stof(values[15]);
    float cstime = stof(values[16]);
    float starttime = stof(values[21]);
    float uptime = ProcessParse::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    result = 100.0 * ((total_time / freq) / seconds);

    return to_string(result);
}


std::string ProcessParse::getProcUpTime(std::string pid)
{
    std::string line;
    std::string value;
    float result;
    ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istring_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    // Using sysconf to get clock ticks of the host machine
    return to_string(float(stof(values[13])/sysconf(_SC_CLK_TCK)));
}
