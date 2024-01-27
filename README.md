directory structure:

app.py
templates -> index.html
trie.cpp
words_alpha.txt

running instructions
dependencies: flask. pip install Flask (probably)
possibly turn off cors browser extension if you run into the issue

gcc trie.cpp -o autocomplete or g++ trie.cpp -o autocomplete
python3 app.py
open the local host link.
