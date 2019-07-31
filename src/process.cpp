#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "../include/process.h"

using std::string;
using std::to_string;
using std::vector;
using std::stoi;
using std::stof;

// TODO: Return this process's ID
int Process::Pid() { return stoi(this->pid); }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return stof(this->cpu); }

// TODO: Return the command that generated this process
string Process::Command() { return this->cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { return this->mem; }

// TODO: Return the user (name) that generated this process
string Process::User() { return this->user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return stoi(this->upTime); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return true; }

string Process::getProcess()
{
    this->mem = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   "
                    + this->user
                    + "   "
                    + this->mem.substr(0,5)
                    + "     "
                    + this->cpu.substr(0,5)
                    + "     "
                    + this->upTime.substr(0,5)
                    + "    "
                    + this->cmd.substr(0,30)
                    + "...");
}