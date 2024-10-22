# CS4437 SCALING FOR RELIAILITY AND PERFORMANCE
## DATA STRUCTURES AND ALGORITHMS
## INSTRUCTOR: EOIN O BRIEN

## TEAM MEMBERS:
- 22340017 Daniel Kennedy
- 22357327 Conor Callanan

## PROJECT DESCRIPTION:
Document indexing, search, and keyword autocomplete

## Project Structure
```bash
.
├── CMakeLists.txt # CMake build information
├── README.md # You are here
├── build # CMake build directory
├── data
│   ├── README.md
│   ├── gutenberg # .txt files from Gutendex
│   ├── gutenberg.sh # script to populate above directory
│   ├── serialized_data
│   │   ├── book_lengths.txt # Number of words in each document in index
│   │   ├── book_paths.txt # Path of each document in index
│   │   ├── frequencies_table.bin # Index, stores frequencies of words per document
│   │   ├── table_width.txt # Number of words in vocabulary
│   │   └── vocab_trie.bin # Persisted Trie for autocomplete & search
│   └── simple_documents # Test documents
├── src
│   ├── core # Data structures
│   │   ├── ArrayList.h
│   │   ├── MaxHeap.hpp
│   │   └── Trie.hpp
│   ├── index # Related to index creation
│   │   ├── FrequencyCounter.hpp # counts word frequencies
│   │   ├── Index.hpp # Index facade
│   │   ├── StringUtils.hpp # Util functions for string manipulation
│   │   └── file
│   │       ├── DocumentSet.hpp # Traverses directory to discover documents
│   │       ├── FileReader.cpp # Reads file
│   │       └── FileReader.hpp # Reads file
│   ├── interface
│   │   └── Autocomplete.hpp # Creates Autocomplete interface for keyword completion
│   ├── main.cpp # Entry point
│   ├── model
│   │   ├── Argument.hpp # Search argument, contains term & metadata (negated, etc)
│   │   ├── Book.hpp # Input document
│   │   └── Result.hpp # Search result
│   └── search
│       ├── Parser.hpp # Search query parser
│       └── Search.hpp # Performs search operation
└── test # gtest test suite
```

## DESIGN CONSIDERATIONS:
- The project will be implemented in C++.
- Use a trie for the autocomplete functionality.
- The trie will also store an index associated with each unique word in the corpus. This references a position in our book index vectors that will store the frequency of that word in that text.
- This approach will achieve constant time for autocomplete (on a letter-by-letter basis) and also constant time for word frequency retrieval.
- The trie will be built during the indexing stage.
- The search functionality will consist of retrieving the frequency of the word from our index 
(on disk) and then using TF-IDF (Term Frequency-Inverse Document Frequency) to assign a value to its importance in the text,
compensated by its frequency in the corpus as a whole.
- A parser and result scoring system enable composition fo search queries using `AND`, `OR` and `NOT` keywords.


*TF-IDF Formula*: 
```math
w{_x}{_,}{_y}=tf{_x}{_,}{_y} × log({N \over df_x})
```

- This will allow us to rank each text by the frequency and importance with which the search term appears, and present the texts to the user in that order.

## Project Infrastructure
- We have chosen CMake as our build system because it is fun and good.
- We have chosen GoogleTest as our testing framework as it has a gentle learning curve and includes features like parameterized testing.
- A bash script pulls the first 100 books from the Gutendex (project Gutenberg public API), and gets rid of those with invalid titles

## CI/CD
- We are using a commit naming convention that uses a code in square brackets to indicate what kind of change the commit is making.
    - **[FEAT]**: Feature Change
    - **[TEST]**: Adding test data
    - **[DOC]**: Documentation change
    - **[REFAC]**: Code refactor
    - **[BUILD]**: Build system related change
    - **[BUG]**: Bug fix
 
- We have configured our automated tests to run on each push to GitHub using GitHub Actions.

## AI Usage:
- Generated example documents with ChatGPT

## Build instructions:
- Go to build directory
- Run `cmake ..`
- Run `make` or `cmake --build .` depending on your system
- Run executable that's produced (e.g. build/Debug/goggle.exe)

## Document procurement
In order to get the documents necessary for searching, use the bash script present in `data/` to download them all.
`cd data`
`source gutenberg.sh`

## Run commands:
- Windows: `cmake --build .\build\ && .\build\Debug\goggle.exe`
- Linux: `cd build && cmake .. && make && ctest && ./bin/google`

- `goggle index`
- `goggle autocomplete`
- `goggle search`
