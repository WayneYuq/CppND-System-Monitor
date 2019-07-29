#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(string pid)
  {
      this->pid = pid;
      this->user = ProcessParse::getProcUser(pid);
      this->mem = ProcessParse::getVmSize(pid);
      this->cmd = ProcessParse::getCmd(pid);
      this->cpu = ProcessParse::getCpuPercent(pid);
      this->upTime = ProcessParse::getProcUpTime(pid);
  }
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  string getProcess();
  
  // TODO: Declare any necessary private members
 private:
  std::string pid;
  std::string user;
  std::string cmd;
  std::string cpu;
  std::string mem;
  std::string upTime;   
};

#endif