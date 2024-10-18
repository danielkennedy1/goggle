#include "ArrayList.h"
#include "DocumentSet.hpp"
#include "FileReader.hpp"
#include "HashMap.hpp"
#include <string>
#include <strings.h>
#include "FrequencyCounter.hpp"

class Index {
public:
    Index(std::string directory) {
        counters = new ArrayList<FrequencyCounter*>;
        DocumentSet* documents = new DocumentSet(directory);
        ArrayList<std::string>* document_paths = documents->getDocumentPaths();

        for (int i = 0; i < document_paths->length; i++) {
            FileReader reader = FileReader(document_paths->get(i));
            ArrayList<std::string>* words = reader.read();

            FrequencyCounter* counter = new FrequencyCounter(words);

            counters->append(counter);
        }
    }

    ArrayList<FrequencyCounter*>* counters = nullptr;
};
