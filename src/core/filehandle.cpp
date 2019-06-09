#include "filehandle.hpp"

FileHandle::FileHandle(const std::string &name, const Fmod fm) {
  if (fm == READ) {
    iFile.open(name, std::fstream::in);
  } else {
    oFile.open(name, std::fstream::out);
  }
}

FileHandle::~FileHandle() {
  iFile.close();
  oFile.close();
}

void FileHandle::writeLine(const std::string &s) { oFile << s << std::endl; }
void FileHandle::writeLine(const std::stringstream &s) { oFile << s.rdbuf() << std::endl; }

void FileHandle::printOut() {
  std::string str;
  while (std::getline(iFile, str)) {
    std::cout << str << std::endl;
  }
}

std::string FileHandle::readLine() {
  std::string str;
  std::getline(iFile, str);
  return str;
}