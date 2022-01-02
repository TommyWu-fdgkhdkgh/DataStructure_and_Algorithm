// time : O(N^2), space : O(N^2)
// 空間複雜度可以更好

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
        
        if(text1[0] == text2[0]){
            dp[0][0] = 1;
        }
        
        for(int i = 1;i < text1.size();i++) {
            if(text1[i] == text2[0]){
                dp[i][0] = 1;
            } else {
                dp[i][0] = dp[i-1][0];
            }
        }
        
        for(int i = 1;i < text2.size();i++) {
            if(text2[i] == text1[0]){
                dp[0][i] = 1;
            } else {
                dp[0][i] = dp[0][i-1];
            }
        }
        
        for(int i = 1;i < text1.size();i++) {
            for(int j = 1;j < text2.size();j++) {
                if(text1[i] == text2[j]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[text1.size()-1][text2.size()-1];
    }
};
