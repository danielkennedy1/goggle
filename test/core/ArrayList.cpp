#include <gtest/gtest.h>
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
