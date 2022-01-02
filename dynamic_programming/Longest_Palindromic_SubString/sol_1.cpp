// time : O(N^2)
// space : O(1)
// 來源：自己
// 跟 https://www.geeksforgeeks.org/longest-palindromic-substring-set-2/ 應該是相同意思

class Solution {
public:
    string longestPalindrome(string s) {
        
        if(s.size() == 0) {
            return s;
        }
        
        int max = -1e9;
        string maxst;
        
        
        int counter;
        //奇數長度的
        for(int i = 0;i < s.size();i++) {
            int left = i-1;
            int right = i+1;
            
            counter = 1;
            
            while(left >= 0 && right < s.size() && s[left] == s[right]) {
                counter+=2;
                left--, right++;
            }
            
            //if(left < 0 || right >= s.size()) {
                left++, right--;
            //}
            
            if(counter > max) {
                max = counter;
                //cout << "max : " << max << endl;
                //cout << "left : " << left << endl;
                maxst = s.substr(left, max);
                //cout << maxst << endl;
            }
        }
        
        //偶數長度的
        for(int i = 0;i < s.size();i++) {
            //int next = i + 1;
            int left = i;
            int right = i+1;
            counter = 0;
            
            //cout << "hihi\n" << endl;
            
            /*if(next < s.size() && s[i] == s[next]) {
                counter = 2;
            } else {
                continue;
            }*/
            
            while(left >= 0 && right < s.size() && s[left] == s[right]) {
                counter+=2;
                left--, right++;
            }
            
            //if(left < 0 || right >= s.size()) {
                left++, right--;
            //}
            
            if(counter > max) {
                max = counter;
                maxst = s.substr(left, max);
                //cout << maxst << endl;
            }
            
        }
        return maxst;
    }
};
