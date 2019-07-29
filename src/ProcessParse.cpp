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
    float result;
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::statPath()));
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = stof(ProcessParse::getProcUpTime(pid)); // 该任务在用户态运行的时间，单位为jiffies
    float stime = stof(values[14]); // 该任务在核心态运行的时间，单位为jiffies
    float cutime = stof(values[15]); // 所有已死线程在用户态运行的时间，单位为jiffies
    float cstime = stof(values[16]); // 所有已死在核心态运行的时间，单位为jiffies
    float starttime = stof(values[21]);
    float uptime = ProcessParse::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK); // 时钟滴答的频率（HZ）：也即1秒时间内PIT所产生的时钟滴答次数
    float total_time = utime + stime + cutime + cstime; // 进程的总Cpu时间，该值包括其所有线程的cpu时间。
    float seconds = uptime - (starttime / freq);
    result = 100.0 * ((total_time / freq) / seconds);

    return to_string(result);
}

// 该任务在用户态运行的时间，单位为jiffies
std::string ProcessParse::getProcUpTime(std::string pid)
{
    std::string line;
    ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istring_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    // Using sysconf to get clock ticks of the host machine
    return to_string(float(stof(values[13])/sysconf(_SC_CLK_TCK)));
}

// 系统运行时间
long int ProcessParse::getSysUpTime()
{
    std::string line;
    ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
    getline(stream, line);
    std::istringstream buf(line);
    std::istring_iterator<string> beg(buf), end;
    std::vector<std::string> values(beg, end);

    return stoi(values[0]);
}

std::string getProcUser(std::string pid)
{

}
