#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return this->pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return this->cpu; }

// TODO: Return the command that generated this process
string Process::Command() { return this->cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { return this->mem; }

// TODO: Return the user (name) that generated this process
string Process::User() { return this->user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return this->upTime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

string Process::getProcess()
{
    this->mem = ProcessParser::getVmSize(this->pid);
    this->up_time = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   "
                    + this->user
                    + "   "
                    + this->mem.substr(0,5)
                    + "     "
                    + this->cpu.substr(0,5)
                    + "     "
                    + this->up_time.substr(0,5)
                    + "    "
                    + this->cmd.substr(0,30)
                    + "...");
}