#include "../include/SysInfo.h"
#include "../include/util.h"

string SysInfo::getCpuPercent() const 
{
    return this->cpuPercent;
}

string SysInfo::getMemPercent() const 
{
    return std::to_string(this->memPercent);
}

long SysInfo::getUpTime() const 
{
    return this->upTime;
}

string SysInfo::getKernelVersion() const 
{
    return this->kernelVer;
}

string SysInfo::getTotalProc() const 
{
    return std::to_string(this->totalProc);
}

string SysInfo::getRunningProc() const 
{
    return std::to_string(this->runningProc);
}

string SysInfo::getThreads() const 
{
    return std::to_string(this->threads);
}

string SysInfo::getOsName() const 
{
    return this->osName;
}

void SysInfo::setLastCpuMeasures()
{
    this->lastCpuStats = ProcessParser::getSysCpuPercent();
}


// This method initializes attributes of the SysInfo class. It takes a size, or number
// of cores, and initializes the object. Besides that, this method sets previous data 
// for a specific CPU core
void SysInfo::getOtherCores(int _size)
{
    //when number of cores is detected, vectors are modified to fit incoming data
    this->cores_stats = vector<string>();
    this->cores_stats.resize(_size);
    this->lastCpuCoresStats = vector<vector<string>>();
    this->lastCpuCoresStats.resize(_size);
    this->currentCpuCoresStats = vector<vector<string>>();
    this->currentCpuCoresStats.resize(_size);
    for (int i = 0; i < _size; i++) {
        this->lastCpuCoresStats[i] = ProcessParser::getSysCpuPercent(std::to_string(i));
    }
}

// This method updates and creates new datasets for CPU calculation. Every core is 
// updated and previous data becomes the current data of calculated measures.
void SysInfo::setCpuCoresStats()
{
    // Getting data from files (previous data is required)
    for(int i = 0; i < this->currentCpuCoresStats.size(); i++) {
        this->currentCpuCoresStats[i] = ProcessParser::getSysCpuPercent(std::to_string(i));
    }
    for(int i = 0; i < this->currentCpuCoresStats.size(); i++) {
        // after acquirement of data we are calculating every core percentage of usage
        this->cores_stats[i] = ProcessParser::printCpuStats(this->lastCpuCoresStats[i],this->currentCpuCoresStats[i]);
    }
    this->lastCpuCoresStats = this->currentCpuCoresStats;
}


// This function initializes or refreshes an object.
void SysInfo::setAttributes() 
{
    // getting parsed data
    this->memPercent = ProcessParser::getSysRamPercent();
    this->upTime = ProcessParser::getSysUpTime();
    this->totalProc = ProcessParser::getTotalNumberOfProcesses();
    this->runningProc = ProcessParser::getNumberOfRunningProcesses();
    this->threads = ProcessParser::getTotalThreads();
    this->currentCpuStats = ProcessParser::getSysCpuPercent();
    this->cpuPercent = ProcessParser::printCpuStats(this->lastCpuStats,this->currentCpuStats);
    this->lastCpuStats = this->currentCpuStats;
    this->setCpuCoresStats();
}

// Constructing string for every core data display
vector<string> SysInfo::getCoresStats() const
{
    vector<string> result = vector<string>();
    for (int i = 0; i < this->cores_stats.size() ;i++) {
        string temp = ("cpu" + std::to_string(i) +": ");
        float check = stof(this->cores_stats[i]);
        if (!check || this->cores_stats[i] == "nan") {
            return vector<string>();
        }
        temp += Util::getProgressBar(this->cores_stats[i]);
        result.push_back(temp);
    }
    return result;
}
