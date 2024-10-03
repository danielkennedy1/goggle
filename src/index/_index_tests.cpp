#include <gtest/gtest.h>
#include "file/FileReader.hpp"

TEST(FileReaderTests, TestWorks)
{
  FileReader *reader = new FileReader("/Users/conor/ISE/Data Structures & Algorithms III/project/goggle/data/simple_documents/11 TestDoc.txt");
  std::vector<std::string> words = reader->read();

  std::string expected_words[4] = {
      "Testing",
      "one",
      "two",
      "three"};

  for (int i = 0; i < words.size(); i++)
  {
    std::string currentWord = words[i].c_str();
    std::string expectedWord = expected_words[i];
    EXPECT_TRUE(currentWord == expectedWord);
  }

  EXPECT_EQ(7 * 6, 42);
}
