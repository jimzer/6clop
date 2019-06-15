#include "core/cyclop.hpp"
#include "core/filehandle.hpp"
#include "gtest/gtest.h"

TEST(filehandle, constructor) {
  FileHandle fh("test.txt", WRITE);
  ASSERT_NO_THROW();
}

TEST(filehandle, writeLine) {
  FileHandle fh("test.txt", WRITE);

  fh.writeLine("test test test test");
  fh.writeLine("test test test test");

  FileHandle fh2("test.txt", READ);
  std::string str;
  str = fh2.readLine();
  str = fh2.readLine();

  ASSERT_EQ(str, "test test test test");

}
