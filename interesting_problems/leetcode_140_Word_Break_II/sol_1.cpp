// 我是靠賽的。。。
//   需要找到更高效的解法！


class Solution {
public:
    
    map<vector<string>, bool> visited;
    
    void DFS(string& s, int index, vector<string>& wordDict, vector<string>& nowvector, vector<vector<string>>& ans) {
        
        if(index == s.size()) {
            
            //cout << "gg" << endl;
            
            ans.push_back(nowvector);
            return;
        }
        
        for(int i = 0;i < wordDict.size();i++) {
            if(s.substr(index, s.size() - index).find(wordDict[i]) == 0) {
                
                //cout << "wordDict[" << i << "] : " << wordDict[i] << endl; 
                //cout << "index : " << index << endl;
                
                nowvector.push_back(wordDict[i]);
                
                if(visited[nowvector] == false) {
                    visited[nowvector] = true;
                    DFS(s, index+wordDict[i].size(), wordDict, nowvector, ans);
                }
                
                nowvector.pop_back();
            }
        }
        
        
        
    }
    
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        
        vector<vector<string>> ans;
        vector<string> nowvector;
        vector<string> real_ans;

        
        vector<int> alphacount_s(26, 0);
        vector<int> alphacount_w(26, 0);
        
        for(int i = 0;i < s.size();i++) {
            alphacount_s[s[i]-'a']++;
        }
        
        for(int i = 0;i < wordDict.size();i++) {
            for(int j = 0;j < wordDict[i].size();j++) {
                alphacount_w[wordDict[i][j]-'a']++;
            }
        }
        
        for(int i = 0;i < 26;i++) {
            if(alphacount_s[i] != 0 && alphacount_w[i] == 0) {
                return real_ans;
            }
        }
        
        
        DFS(s, 0, wordDict, nowvector, ans);
        
        
        string temp = "";
        for(int i = 0;i < ans.size();i++) {
            for(int j = 0;j < ans[i].size();j++) {
                if(j == ans[i].size()-1) {
                    temp = temp + ans[i][j];
                } else {
                    temp = temp + (ans[i][j] + " ");
                }
            }
            
            real_ans.push_back(temp);
            temp = "";
        }
        
        return real_ans;
        
    }
};
