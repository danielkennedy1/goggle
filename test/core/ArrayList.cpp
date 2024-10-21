#include <gtest/gtest.h>
#include <cstring>
#include <filesystem>
#include "ArrayList.h"

TEST(ArrayListTests, TestInsertionAndDeletion) {
    ArrayList<std::string>* arraylist = new ArrayList<std::string>();

    arraylist->append("one");
    arraylist->append("two");
    arraylist->append("three");

    arraylist->remove(1);

    ASSERT_EQ(arraylist->get(0), "one");
    ASSERT_EQ(arraylist->get(1), "three");
}


TEST(ArrayListTests, TestUpdate) {
    ArrayList<std::string>* arraylist = new ArrayList<std::string>();

    arraylist->append("one");
    arraylist->append("two");
    arraylist->append("three");

    arraylist->update(1, "four");

    ASSERT_EQ(arraylist->get(0), "one");
    ASSERT_EQ(arraylist->get(1), "four");
    ASSERT_EQ(arraylist->get(2), "three");
}

TEST(ArrayListTests, TestSerializationDeserialization) {
    ArrayList<std::string>* arraylist = new ArrayList<std::string>();

    arraylist->append("one");
    arraylist->append("two");
    arraylist->append("three");

    arraylist->update(1, "four");

     std::filesystem::path filepath = std::string(SERIALIZED_DATA_DIR);
    bool filepathExists = std::filesystem::is_directory(filepath);
    
    std::string documentsPath = SERIALIZED_DATA_DIR;

    if(!filepathExists) {
        std::filesystem::create_directory(filepath);
    }

    arraylist->serialize(documentsPath + "/testing_arraylist_serialization");

    ArrayList<std::string> deserArrayList = ArrayList<std::string>::deserialize(documentsPath + "/testing_arraylist_serialization");

    std::remove((documentsPath + "/testing_arraylist_serialization").c_str());

    ASSERT_TRUE(0 == std::memcmp(arraylist->array, deserArrayList.array, arraylist->size));
}