#!/bin/bash

rm -rf ./gutenberg
mkdir -p ./gutenberg

for i in {1..100}
do
    url="https://www.gutenberg.org/ebooks/${i}.txt.utf-8"
    wget -q "$url" -O "./gutenberg/${i}.txt.utf-8"
    
    # Title of document is in the file
    title=$(grep -m 1 "^Title: " "./gutenberg/${i}.txt.utf-8" | sed 's/Title: //' | tr -d '\r')

    clean_title=$(echo "$title" | sed 's/[\/:*?"<>|]/_/g')
    
    mv "./gutenberg/${i}.txt.utf-8" "./gutenberg/${clean_title}.txt"
    
    echo "${clean_title}.txt"
done

echo "All files processed!"
