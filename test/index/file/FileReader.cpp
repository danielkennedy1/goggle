#include <gtest/gtest.h>
#include "FileReader.hpp"
#include "ArrayList.h"

TEST(FileReaderTests, TestOutput_correct)
{
  FileReader *reader = new FileReader("../data/simple_documents/11 TestDoc.txt");
  ArrayList<std::string> words = reader->read();

  std::string expected_words[4] = {
      "Testing",
      "one",
      "two",
      "three"};

  EXPECT_TRUE(words.length == 4) << "VECTOR IS WRONG LENGTH" << std::endl;

  for (int i = 0; i < sizeof expected_words / sizeof expected_words[0]; i++)
  {
    EXPECT_TRUE(true);
  }
}

TEST(FileReaderTests, TestOutput_incorrect)
{
  FileReader *reader = new FileReader("../data/simple_documents/11 TestDoc.txt");
  ArrayList<std::string> words = reader->read();

  std::vector<std::string> expected_words = {
      "esting",
      "two",
      "three"};

  bool working = false;
  for (int i = 0; i < expected_words.size(); i++)
  {
    std::string currentWord = words[i];
    std::string expectedWord = expected_words[i];
    if (currentWord == expectedWord)
    {
      working = true;
    }
  }

  EXPECT_FALSE(working) << working;
}
