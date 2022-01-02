//time : O(N^2)

class Solution {
public:
    
    int dfs(string& s, vector<vector<int>>& dp, int left, int right) {
        if(left == 0 || right == 0) {
            return 0;
        } else if(left > right){
            return 0;
        } else if(left == right){
            //printf("left : %d\n", left);
            dp[left][right] = 1;
            return 1;
        } else if(dp[left][right] != 0) {
            return dp[left][right];
        }
        
        if(s[left-1] == s[right-1]) {
            dp[left][right] = dfs(s, dp, left+1, right-1) + 2;
        } else {
            dp[left][right] = max(dfs(s, dp, left+1, right), dfs(s, dp, left, right-1));
        }
        
        return dp[left][right];
        
    }
    
    int longestPalindromeSubseq(string s) {
        
        if(s.size() == 0) {
            return 0;
        } else if(s.size() == 1) {
            return 1;
        }
        
        vector<vector<int>> dp(s.size()+1, vector<int>(s.size()+1, 0));
        
        //int result  = dfs(s, dp, 1, s.size());
        
        /*for(int i = 0;i < s.size()+1;i++) {
            for(int j = 0;j < s.size()+1;j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[1][s.size()];*/
        return dfs(s, dp, 1, s.size());
        
    }
};
