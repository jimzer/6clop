#ifndef FILEHANDLEH
#define FILEHANDLEH

#include <fstream>
#include <iostream>
#include "core/cyclop.hpp"

enum Fmod { READ, WRITE };

class FileHandle {
 private:
  std::ofstream oFile;
  std::ifstream iFile;

  FileHandle(const FileHandle &);
  FileHandle &operator=(const FileHandle &);

 public:
  FileHandle(const std::string &name, const Fmod fm);
  ~FileHandle();

  void writeLine(const std::string &s);
  void writeLine(const std::stringstream &s);
  void printOut();
  std::string readLine();
};

#endif