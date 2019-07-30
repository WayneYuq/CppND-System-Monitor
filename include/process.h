#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "ProcessParser.h"
using std::string;

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(string pid)
  {
      this->pid = pid;
      this->user = ProcessParser::getProcUser(pid);
      this->mem = ProcessParser::getVmSize(pid);
      this->cmd = ProcessParser::getCmd(pid);
      this->cpu = ProcessParser::getCpuPercent(pid);
      this->upTime = ProcessParser::getProcUpTime(pid);
  }
  int Pid();                               // TODO: See src/process.cpp
  string User();                      // TODO: See src/process.cpp
  string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  string getProcess();
  
  // TODO: Declare any necessary private members
 private:
  string pid;
  string user;
  string cmd;
  string cpu;
  string mem;
  string upTime;   
};

#endif