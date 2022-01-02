// 在 TLE 邊緣的鱉腳解法，看看解答是怎麼解開這題的！
//   看了解答後，真心覺得解答真的太厲害了。先對所有字串進行前處理，雖然前處理看起來很花時間，但其實在複雜度上算是還好，最後就可以用 hash 來判斷是否為相鄰的字串，而不需要使用遍尋

class Solution {
public:
    
    int ans = 1e9;
    bool found = false;
    
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        int flag = false;
        int goalindex;
        for(int i = 0;i < wordList.size();i++) {
            if(wordList[i] == endWord) {
                goalindex = i;
                flag = true;
            }
        }
        if(flag == false) {
            return 0;
        }
        
        //unordered_map<string, bool> visited;
        vector<bool> visited(wordList.size()+1, false);

        queue<int> q;
        
        //q.push(wordList.size());
        //visited[wordList.size()] = true;
        int nowmaxlen = 0;
        int nextmaxlen = 0;
        int depth = 0;
        int counter = 0;
        
        for(int i = 0;i < wordList.size();i++) {
            counter = 0;
            for(int j = 0;j < wordList[i].size();j++) {
                if(wordList[i][j] != beginWord[j]) {
                    counter++;
                }
                
                if(counter > 1) {
                    break;
                }
                
            }
            
            if(counter == 1) {
                q.push(i);
                visited[i] = true;
                nowmaxlen++;
            }
        }
        
        
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            
            //cout << "now : " << wordList[now] << endl;
            //cout << "now :" << now << endl; 
            
            if(now == goalindex) {
                found = true;
                //cout << "goalindex : " << goalindex << ", now : " << now << endl;
                break;
            }
            
            
            for(int i = 0;i < wordList.size();i++) {
                
                if(visited[i] == false) {
                    counter = 0;
                    for(int j = 0;j < wordList[i].size();j++) {
                        if(wordList[i][j] != wordList[now][j]) {
                            counter++;
                        }
                        
                        if(counter > 1) {
                            break;
                        }
                    }
                    
                    if(counter == 1) {
                        visited[i] = true;
                        q.push(i);
                        nextmaxlen++;
                    }
                    
                }
            }
            /*for(int i = 1;i < newdic[now].size();i++) {
                if(visited[newdic[now][i]] == false) {
                    visited[newdic[now][i]] = true;
                    q.push(newdic[now][i]);
                    nextmaxlen++;
                }
            }*/
            
            nowmaxlen--;
            
            if(nowmaxlen == 0) {
                depth++;
                nowmaxlen = nextmaxlen;
                nextmaxlen = 0;
            }   
        }
                
        if(found) {
            return depth+2;
        } else {
            return 0;
        }
        
        
    }
};
