# CS4437 SCALING FOR RELIAILITY AND PERFORMANCE
## DATA STRUCTURES AND ALGORITHMS
## INSTRUCTOR: EOIN O BRIEN

## TEAM MEMBERS:
- 22340017 Daniel Kennedy
- 22357327 Conor Callanan

## PROJECT DESCRIPTION:
Document indexing, search, and keyword autocomplete

## DESIGN CONSIDERATIONS:
- The project will be implemented in C++.
- Use a trie for the autocomplete functionality.
- The trie will also store an index associated with each unique word in the corpus. This references a position in our book index vectors that will store the frequency of that word in that text.
- This approach will achieve constant time for autocomplete (on a letter-by-letter basis) and also constant time for word frequency retrieval.
- The trie will be built during the indexing stage.
- The search functionality will consist of retrieving the frequency of the word from our index and then using TF-IDF (Term Frequency-Inverse Document Frequency) to assign a value to its importance in the text, compensated by its frequency in the corpus as a whole.

*TF-IDF Formula*: 
```math
w{_x}{_,}{_y}=tf{_x}{_,}{_y} × log({N \over df_x})
```

- This will allow us to rank each text by the frequency and importance with which the search term appears, and present the texts to the user in that order.

## Project Infrastructure
- We have chosen CMake as our build system because it is fun and good.
- We have chosen GoogleTest as our testing framework as it has a gentle learning curve and includes features like parameterized testing.

## CI/CD
- We are using a commit naming convention that uses a code in square brackets to indicate what kind of change the commit is making.
    - **[FEAT]**: Feature Change
    - **[TEST]**: Adding test data
    - **[DOC]**: Documentation change
    - **[REFAC]**: Code refactor
    - **[BUILD]**: Build system related change

## NOTES:
- I reckon we should seperate the file ingress and index creation from each other so its easier to test.


## AI Usage:
- Generated example documents with ChatGPT

## Build instructions:
- Go to build directory
- Run `cmake ..`
- Run `make` or `cmake --build .` depending on your system
- Run executable that's produced (e.g. build/Debug/goggle.exe)

## Document procurement
`cd data`
`source gutenberg.sh`

## Run commands:
- Daniel: `cmake --build .\build\ && .\build\Debug\goggle.exe`
