#include <ncurses.h>
#include <form.h>
#include "ArrayList.h"
#include "Trie.hpp"

class Autocomplete {

    public:
        Autocomplete(TrieNode* vocabTrie) : vocabTrie(vocabTrie) {};

        void start() {
            initscr();
            noecho();

            printw("Welcome to Goggle autocomplete! Start typing and see to see suggestions appear! (Ctrl D to exit)");

            ArrayList<std::string> wordSuggestions;

            std::string input;

            char c;

            while (c != '\x04') {  // Ctrl+D to exit
                c = getch();

                if(c == 127) {
                    if (input.size() > 0) {
                        input.pop_back();
                        wordSuggestions = vocabTrie->autocomplete(input);
                        clear();
                        move(0,0);
                        refresh();
                        for (int i = 0; i < 5; i++) {
                            if (wordSuggestions.length > i) {
                                printw((wordSuggestions[i] + "\n").c_str());
                            } else {
                                printw("-------------------\n");
                            }
                        }
                        printw(input.c_str());
                    }
                }
                if(c == 32) {
                    continue;
                }
                if (!(c <= 122 && c >= 65) || (c > 90 && c < 97)) {
                    continue;
                }
                if (c <= 90) {
                    c += 32;
                }


                input += c;

                wordSuggestions = vocabTrie->autocomplete(input);

                clear();
                move(0,0);
                refresh();
                for (int i = 0; i < 5; i++) {
                    if (wordSuggestions.length > i) {
                        printw((wordSuggestions[i] + "\n").c_str());
                    } else {
                        printw("-------------------\n");
                    }
                }
                printw(input.c_str());  
                }

            endwin();
        };


    TrieNode* vocabTrie;
};
