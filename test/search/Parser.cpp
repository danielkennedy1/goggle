
#include <gtest/gtest.h>
#include "Parser.hpp"
#include "FileReader.hpp"
#include "FrequencyCounter.hpp"


TEST(ParserTests, TestParseQueryAnd)
{
    std::string s(TEST_DATA_DIR);
    FileReader *reader = new FileReader(s + "/8 Files.txt");
    
    ArrayList<std::string>* words = reader->read();

    FrequencyCounter counter = FrequencyCounter(1);

    counter.addDocument(0, words, StringUtils::parseDocNameFromPath(s + "/8 Files.txt"));

    counter.indexDocument(0);

    ArrayList<int> documentFrequencies = counter.getFreqTable()[0];

    TrieNode* vocabTrie = counter.getVocabTrie();

    std::string query = "file aNd Data";

    Parser parser(query);

    ArrayList<Argument> args = parser.parse();

    ASSERT_EQ(args[0].word, "data");
    ASSERT_EQ(args[0].negated, false);
    ASSERT_EQ(args[0].required, true);
    ASSERT_EQ(args[1].word, "file");
    ASSERT_EQ(args[1].negated, false);
    ASSERT_EQ(args[1].required, true);
}



TEST(ParserTests, TestParseQueryOr)
{
    std::string s(TEST_DATA_DIR);
    FileReader *reader = new FileReader(s + "/8 Files.txt");
    
    ArrayList<std::string>* words = reader->read();

    FrequencyCounter counter = FrequencyCounter(1);

    counter.addDocument(0, words, StringUtils::parseDocNameFromPath(s + "/8 Files.txt"));

    counter.indexDocument(0);

    ArrayList<int> documentFrequencies = counter.getFreqTable()[0];

    TrieNode* vocabTrie = counter.getVocabTrie();

    std::string query = "file OR Data";

    Parser parser(query);

    ArrayList<Argument> args = parser.parse();

    ASSERT_EQ(args[0].word, "data");
    ASSERT_EQ(args[0].negated, false);
    ASSERT_EQ(args[0].required, false);
    ASSERT_EQ(args[1].word, "file");
    ASSERT_EQ(args[1].negated, false);
    ASSERT_EQ(args[1].required, false);
}


TEST(ParserTests, TestParseQueryNot)
{
    std::string s(TEST_DATA_DIR);
    FileReader *reader = new FileReader(s + "/8 Files.txt");
    
    ArrayList<std::string>* words = reader->read();

    FrequencyCounter counter = FrequencyCounter(1);

    counter.addDocument(0, words, StringUtils::parseDocNameFromPath(s + "/8 Files.txt"));

    counter.indexDocument(0);

    ArrayList<int> documentFrequencies = counter.getFreqTable()[0];

    TrieNode* vocabTrie = counter.getVocabTrie();

    std::string query = "not file OR Data";

    Parser parser(query);

    ArrayList<Argument> args = parser.parse();

    ASSERT_EQ(args[0].word, "data");
    ASSERT_EQ(args[0].negated, false);
    ASSERT_EQ(args[0].required, false);
    ASSERT_EQ(args[1].word, "file");
    ASSERT_EQ(args[1].negated, true);
    ASSERT_EQ(args[1].required, false);
}
