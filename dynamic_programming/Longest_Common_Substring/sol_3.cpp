// 題目網址 ： https://leetcode.com/problems/maximum-length-of-repeated-subarray/
// time : O(n*m)
// space : O(n*m)
// 來源： https://www.geeksforgeeks.org/longest-common-substring-dp-29/
//  dynamic programming

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        
        
        int maxlen = 0;
        
        vector<vector<int>> dp(A.size(), vector<int>(B.size(), 0));
        // dp[i][j] means :
        //  length of common suffix end at index i and j
        
        for(int i = 0;i < A.size();i++) {
            if(A[i] == B[0]) {
                dp[i][0] = 1;
                
                if(dp[i][0] > maxlen) {
                    maxlen = 1;
                }
                
            } 
        }
        
        for(int i = 0;i < B.size();i++) {
            if(A[0] == B[i]) {
                dp[0][i] = 1;
                
                if(dp[0][i] > maxlen) {
                    maxlen = 1;
                }
                
            }
        }
        
        for(int i = 1;i < A.size();i++) {
            for(int j = 1;j < B.size();j++) {
                if(A[i] == B[j]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    
                    if(dp[i][j] > maxlen) {
                        maxlen = dp[i][j];
                    }
                    
                }
            }
        }
    
        return maxlen;
        
    }
};
