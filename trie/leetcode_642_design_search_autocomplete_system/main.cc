
#define ALPHA_NUMS 256

struct TrieNode {
    //char data;
    int times;
    string st;
    bool isLeaf;
    struct TrieNode *next[ALPHA_NUMS];
};

bool trieNodeCompare(TrieNode *a, TrieNode *b) {
    if(a->times == b->times) {
        return a->st < b->st;
    }
    return a->times > b->times; 
}

class AutocompleteSystem {
private:
    struct TrieNode *triehead = NULL;
    struct TrieNode *lasthead = NULL;
    bool firstFlag = true;
    string nowst;
public:
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        triehead = new TrieNode;
        
        for(int i = 0;i < ALPHA_NUMS;i++) {
            triehead->next[i] = NULL;
        }
        
        triehead->isLeaf = true;
        triehead->times = 0;
        
        for(int i = 0;i < sentences.size();i++) {
            insert(sentences[i], times[i]);
        }
    }
    
    vector<string> input(char c) {
        vector<string> v;
        
        if(c  == '#') {
            insert(nowst, 1);
            nowst.clear();
            firstFlag = true;
            lasthead = NULL;
            return v;
        } else {
            vector<TrieNode *> tempv; 
            queue<TrieNode *> q;
            
            nowst += c;
            
            if(firstFlag == false && lasthead == NULL) {
                return v;
            }
            
            firstFlag = false;
                        
            if(lasthead == NULL) {
                q.push(triehead->next[c]);
            } else {
                q.push(lasthead->next[c]);
            }
            lasthead = q.front();
            
            if(lasthead == NULL) {
                return v;
            }
            
            while(!q.empty()) {
                TrieNode *nown = q.front();
                q.pop();
                                
                if(nown->isLeaf) {
                    //cout << nown->st << endl;
                    tempv.push_back(nown);
                }
                
                for(int i = 0;i < ALPHA_NUMS;i++) {
                    if(nown->next[i] != NULL) {
                        q.push(nown->next[i]);
                    }
                }
            }
            
            sort(tempv.begin(), tempv.end(), trieNodeCompare);
            
            //printf("tempv.size() : %lu\n", tempv.size());
            for(int i = 0;i < tempv.size() && i < 3;i++) {
                v.push_back(tempv[i]->st);
            }
        }
        
        return v;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word, int times) {
        struct TrieNode *pnow;
        pnow = triehead;

        for(int i = 0;i < word.size();i++) {

            if(pnow->next[word[i]] == NULL) {
                pnow->next[word[i]] = new TrieNode;
                pnow = pnow->next[word[i]];

                //pnow->data = word[i];
                for(int j = 0;j < ALPHA_NUMS;j++) {
                    pnow->next[j] = NULL;
                }
                pnow->isLeaf = false;
            } else {
                pnow = pnow->next[word[i]];
            }
        }

        if(pnow->isLeaf) {
            pnow->times++;
        } else {
            pnow->times = times;
            pnow->st = word;
            pnow->isLeaf = true;
        }
    }

    
};

