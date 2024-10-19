
#include <gtest/gtest.h>
#include "Parser.hpp"
#include "FileReader.hpp"
#include "FrequencyCounter.hpp"


TEST(ParserTests, TestParseQuery)
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

    Parser parser(query, vocabTrie);

    Argument* args = parser.parse();

    ASSERT_EQ(args[0].index, 1);
    ASSERT_EQ(args[0].negated, false);
    ASSERT_EQ(args[0].required, true);
    ASSERT_EQ(args[1].index, 6);
    ASSERT_EQ(args[1].negated, false);
    ASSERT_EQ(args[1].required, true);
}
