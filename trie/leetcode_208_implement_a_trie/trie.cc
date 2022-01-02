#include <iostream>
#include <cstdio>

using namespace std;

#define ALPHA_NUMS 26

struct TrieNode {
    struct TrieNode *next[ALPHA_NUMS];
    //char data;
    bool isLeaf;
};



class Trie {
private:
    struct TrieNode *triehead;

public:
    
    /** Initialize your data structure here. */
    Trie() {
        triehead = new TrieNode;
        
        for(int i = 0;i < ALPHA_NUMS;i++) {
            triehead->next[i] = NULL;
        }
        
        //triehead->data = 0;
        triehead->isLeaf = true;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        struct TrieNode *pnow;
        pnow = triehead;
        
        
        for(int i = 0;i < word.size();i++) {
            
            if(pnow->next[word[i]-'a'] == NULL) {
                pnow->next[word[i]-'a'] = new TrieNode;
                pnow = pnow->next[word[i]-'a'];
                
                //pnow->data = word[i];
                for(int j = 0;j < ALPHA_NUMS;j++) {
                    pnow->next[j] = NULL;
                }
                pnow->isLeaf = false;
            } else {
                pnow = pnow->next[word[i]-'a'];
            }
        }
        
        pnow->isLeaf = true;
                
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        
        struct TrieNode *pnow = triehead;
        
        for(int i = 0;i < word.size();i++) {
            
            if(pnow->next[word[i] - 'a'] == NULL) {
                return false;
            }
            
            pnow = pnow->next[word[i] - 'a'];
        }
                
        if(pnow->isLeaf) {
            return true;
        }    
        
        return false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        
        struct TrieNode *pnow = triehead;
        
        for(int i = 0;i < prefix.size();i++) {
            if(pnow->next[prefix[i] - 'a'] == NULL) {
                return false;
            }
            
            pnow = pnow->next[prefix[i] - 'a'];
        }
        
        return true;

    }
};


int main(int argc, char *argv[]) {
    string word;
    cin >> word;
    string prefix;
    cin >> prefix; 

    Trie* obj = new Trie();
    obj->insert(word);
    bool param_2 = obj->search(word);
    bool param_3 = obj->startsWith(prefix);

    param_2 == true ? cout << "parame_2 is true" << endl : cout << "parame_2 is false" << endl;
    param_3 == true ? cout << "parame_3 is true" << endl : cout << "parame_3 is false" << endl;

    return 0;
}
