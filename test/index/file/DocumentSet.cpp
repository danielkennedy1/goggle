#include <gtest/gtest.h>
#include "DocumentSet.hpp"
#include "ArrayList.h"

TEST(DocumentSetTests, TestNumberOfTxtFiles_Correct) {
    DocumentSet documentSet = DocumentSet(TEST_DATA_DIR);

    ArrayList<std::string>* paths = documentSet.getDocumentPaths();

    ASSERT_EQ(paths->length, 11) << "Unexpected number of files in test directory.";
}
