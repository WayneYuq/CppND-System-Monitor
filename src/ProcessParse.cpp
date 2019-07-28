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

long int ProcessParse::getSysUpTime()
{
    std::string line;
    ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istring_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    return stoi(values[0]);
}

std::string ProcessParse::getProcUser(std::string pid)
{
    string line;
    string name = "Uid:";
    string result = "";
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
    while (std::getline(stream, line))
    {
        if (line.compare(0, name.size(), name) == 0) {
            istringstream buf(line);
            isteam_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            result = values[1];
            break;
        }
    }

    stream = Util::getStream("/etc/passwd");
    name = ("x:" + result);
    // Search name with UID
    while (getline(stream, line))
    {
        if (line.find(name) != std::string::npos) {
            result = line.substr(0, line.find(":"));
            return result;
        }
    }
}

vector<string> ProcessParse::getPidlist()
{
    DIR* dir;
    // Basically, we are scanning /proc dir for all directories with numbers as their names
    // If we get valid check we store dir names in vector as list of machine pids
    vector<string> container;
    if(!(dir == opendir("/proc")))
        throw std::runtime_error(std::strerror(errno));

    while (dirent* dirp = readdir(dir))
    {
        // check directory
        if (dirp->d_type != DT_DIR)
            continue;
        
        if (all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c){ return std::isdigit(c); }))
            container.push_back(dirp->d_name);
    }

    if (closedir(dir))
        throw std::runtime_error(std::strerror(errno));
    
    return container;
}

string ProcessParse::getCmd(string pid)
{
    string line;
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::cmdPath()));
    std::getline(stream, line);
    return line;
}

int ProcessParse::getNumberOfCores()
{
    string line;
    string name = "cpu cores";
    ifstream stream = Util::getStream((Path::basePath() + "cpuinfo"));
    while (std::getline(stream, line))
    {
        if (line.compare(0, name.size(), name) == 0){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            return stoi(values[3]);
        }
    }
    return 0;
}

vector<string> ProcessParser::getSysCpuPercent(string coreNumber)
{
    // It is possible to use this method for selection of data for overall cpu or every core.
    // when nothing is passed "cpu" line is read
    // when, for example "0" is passed  -> "cpu0" -> data for first core is read
    string line;
    string name = "cpu" + coreNumber;
    ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(),name) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            // set of cpu data active and idle times;
            return values;
        }
    }
    return (vector<string>());
}

float get_sys_active_cpu_time(vector<string> values)
{
    return (stof(values[S_USER]) + 
            stof(values[S_NICE]) +
            stof(values[S_SYSTEM]) +
            stof(values[S_IRQ]) +
            stof(values[S_SOFTIRQ]) +
            stof(values[S_STEAL]) +
            stof(values[S_GUEST]) +
            stof(values[S_GUEST_NICE]));
}

float get_sys_idle_cpu_time(vector<string> values)
{
    return (stof(values[s_IDLE]) + stof(values[S_IOWAIT]));
}

string ProcessParse::printCpuStats(vector<string> values1, vector<string> values2)
{
    float activeTime = get_sys_active_cpu_time(values2) - get_sys_active_cpu_time(values1);
    float idleTime = get_sys_idle_cpu_time(values2) - get_sys_idle_cpu_time(values1);
    float totalTime = activeTime + idleTime;
    float result = 100.0 * (activeTime / totalTime);
    return to_string(result);
}

float ProcessParser::getSysRamPercent()
{
    string line;
    string name1 = "MemAvailable:";
    string name2 = "MemFree:";
    string name3 = "Buffers:";

    string value;
    int result;
    ifstream stream = Util::getStream((Path::basePath() + Path::memInfoPath()));
    float total_mem = 0;
    float free_mem = 0;
    float buffers = 0;
    while (std::getline(stream, line)) {
        if (total_mem != 0 && free_mem != 0)
            break;
        if (line.compare(0, name1.size(), name1) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            total_mem = stof(values[1]);
        }
        if (line.compare(0, name2.size(), name2) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            free_mem = stof(values[1]);
        }
        if (line.compare(0, name3.size(), name3) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            buffers = stof(values[1]);
        }
    }
    //calculating usage:
    return float(100.0*(1-(free_mem/(total_mem-buffers))));
}

string ProcessParser::getSysKernelVersion()
{
    string line;
    string name = "Linux version ";
    ifstream stream = Util::getStream((Path::basePath() + Path::versionPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(),name) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            return values[2];
        }
    }
    return "";
}

string ProcessParser::getOsName()
{
    string line;
    string name = "PRETTY_NAME=";

    ifstream stream = Util::getStream(("/etc/os-release"));

    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
              std::size_t found = line.find("=");
              found++;
              string result = line.substr(found);
              result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
              return result;
        }
    }
    return "";

}

int ProcessParser::getTotalThreads()
{
    string line;
    int result = 0;
    string name = "Threads:";
    vector<string>_list = ProcessParser::getPidList();
    for (int i=0 ; i<_list.size();i++) {
        string pid = _list[i];
        //getting every process and reading their number of their threads
        ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
        while (std::getline(stream, line)) {
            if (line.compare(0, name.size(), name) == 0) {
                istringstream buf(line);
                istream_iterator<string> beg(buf), end;
                vector<string> values(beg, end);
                result += stoi(values[1]);
                break;
            }
        }
    }
    return result;
}

int ProcessParser::getTotalNumberOfProcesses()
{
    string line;
    int result = 0;
    string name = "processes";
    ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            result += stoi(values[1]);
            break;
        }
    }
    return result;
}

int ProcessParser::getNumberOfRunningProcesses()
{
    string line;
    int result = 0;
    string name = "procs_running";
    ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            result += stoi(values[1]);
            break;
        }
    }
    return result;
}