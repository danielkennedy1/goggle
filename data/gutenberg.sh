#!/bin/bash

rm -rf ./gutenberg
mkdir -p ./gutenberg

for i in {1..3}
do
    url="https://www.gutenberg.org/ebooks/${i}.txt.utf-8"
    wget -q "$url" -O "./gutenberg/${i}.txt.utf-8"
    
    # Title of document is (usually) in the file
    title=$(grep -m 1 "^Title: " "./gutenberg/${i}.txt.utf-8" | sed 's/Title: //' | tr -d '\r')

    clean_title=$(echo "$title" | sed 's/[\/:*?"<>| ]/_/g' | iconv -f UTF-8 -t ASCII//TRANSLIT)
    
    iconv -f UTF-8 -t ASCII//TRANSLIT -c "./gutenberg/${i}.txt.utf-8" >  "./gutenberg/${clean_title}.txt"

    rm "./gutenberg/${i}.txt.utf-8" 
    
    echo "${clean_title}.txt"
done

echo "All files processed!"
