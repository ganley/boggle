#include <assert.h>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;



class Trie
{
public:
    Trie() : _end(false)
    {
        for (int i = 0; i < 26; ++i) _children[i] = nullptr;
    }
    ~Trie()
    {
        for (int i = 0; i < 26; ++i) delete _children[i];
    }

    void insert(const std::string& str, const int pos = 0)
    {
        assert(str[pos] >= 'a' && str[pos] <= 'z');
        const int ix = str[pos] - 'a';
        Trie* child = getChild(ix);
        if (pos == str.length() - 1) {
            child->_end = true;
        } else {
            child->insert(str, pos + 1);
        }
    }

    Trie* getChild(const int ix)
    {
        if (_children[ix] == nullptr) {
            _children[ix] = new Trie();
        }
        return _children[ix];
    }

public:
    Trie* _children[26];
    bool _end = false;
};



void search(char board[4][4],
            int r,
            int c,
            Trie* trie,
            set<string>& emitted,
            bool visited[4][4],
            string str = "")
{
    if (trie == nullptr) {
        return;
    }
    if (trie->_end) {
        if (emitted.find(str) == emitted.end()) {
            cout << str << "\n";
            emitted.insert(str);
        }
    }

    const char ch = board[r][c];
    visited[r][c] = true;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            const int nr = r + dr;
            const int nc = c + dc;
            if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4 && !visited[nr][nc]) {
                search(board, nr, nc, trie->_children[ch - 'a'], emitted,
                       visited, str + ch);
            }
        }
    }
    visited[r][c] = false;
}



int main(int argc, char* argv[])
{
    const int MIN_LENGTH = 4;
    const string LOWERALPHAS("abcdefghijklmnopqrstuvwxyz");
    //const char* wordfile = "/usr/share/dict/words";
    const char* wordfile = "common_words.txt";

    auto in = ifstream(wordfile);
    string word;
    Trie* root = new Trie();
    while (in >> word) {
        if (word.length() < MIN_LENGTH || word.length() > 16) {
            continue;
        }
        if (word.find_first_not_of(LOWERALPHAS) != string::npos) {
            continue;
        }

        root->insert(word);
    }

    // read board
    char board[4][4];
    std::string row;
    for (int i = 0; i < 4; ++i) {
        cin >> row;
        assert(row.length() == 4);
        strcpy(board[i], row.c_str());
        for (int j = 0; j < 4; ++j) {
            assert(board[i][j] >= 'a' && board[i][j] <= 'z');
        }
    }

    // search for words
    set<string> emitted;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            bool visited[4][4] = {false};
            search(board, i, j, root, emitted, visited);
        }
    }

    delete root;

    return 0;
}
