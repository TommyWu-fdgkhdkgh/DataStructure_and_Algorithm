// time : O(N^2)
// space : O(N^2)
// 來源：https://www.geeksforgeeks.org/longest-palindrome-substring-set-1/


class Solution {
public:
    string longestPalindrome(string s) {
        
        if(s.size() == 0) {
            return s;
        }
        
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false)); 
        
        int left;
        int anslen = -1e9;
        
        for(int i = 0;i < s.size();i++) {
            // odd
            dp[i][i] = true;
            
            //even
            if(i != 0 && s[i] == s[i-1]) {
                dp[i-1][i] = true;
            }
        }
        
        for(int i = 3;i <= s.size();i++) {
            //cout << "i : " << i << endl;
            for(int j = 0;(j+i-1) < s.size();j++) {
                int right = j+i-1;
                
                if(s[j] == s[right] && dp[j+1][right-1]) {
                    dp[j][right] = true;
                }
            }
        }
        
        for(int i=0;i < s.size();i++) {
            for(int j = i;j < s.size();j++) {
                int temp = j-i+1;
                if(temp > anslen && dp[i][j]) {
                    left = i;
                    anslen = temp;
                }
            }
        }
        
        
        
        return s.substr(left, anslen);
        
        
    }
};
