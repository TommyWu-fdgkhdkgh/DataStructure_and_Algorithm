// leetcode
// time : O(N)
// space : O(N)


//manacher's algorithm
//https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size() == 0) {
            return s;
        }
        
        // LPS : 以 index 為中心點的 palindromic substring 長度
        vector<int> LPS(s.size()*2+1, 0);
        
        int centerPosition = 1;
        int centerLeftPosition = 0;
        int centerRightPosition = 2;
        
        int currentLeftPosition;
        int currentRightPosition;
        
        int longestLPS = 1;
        int longestCenterPosition = 1;
        
        int lenOfPosition = s.size()*2+1;
        
        LPS[0] = 0;
        LPS[1] = 1;
        
        int expansion;   // 當 case 3, case 4 出現的時候，就需要往旁邊找
        int expanindex;
        int diff;        // centerRightPosition - currentRightPosition
        
        
        for(int i = 2;i < lenOfPosition;i++) {
            currentRightPosition = i;
            
            // centerPosition - (currentRightPosition - centerPosition)
            currentLeftPosition = 2*centerPosition - currentRightPosition;
            
            diff = centerRightPosition - currentRightPosition;
            expansion = 0;
            
            //manacher's algorithm 利用了“鏡像”的概念
            //假若有一個較長的 palindromic substring ，左右兩邊各有一個 palindromic substring
            //   則左右兩邊的 palindromic substring 會存在某種對稱的關係
            //   然而有無完全對稱，仍有一定的限制（須符合 case1, case2）
            //   沒辦法完全對稱的情況下（case3, case4），再對兩邊進行線性的遍尋
            
            
            // 現在令較長的 palindromic substring 為 A
            //      左側的 palindromic substring 為 B
            //      右側的 palindromic substring 為 C
            if(diff >= 0) {
            
                
                if(diff > LPS[currentLeftPosition]) {
                    //case 1
                    // B 跟 C 沒有超出 A 範圍的可能性
                    
                    LPS[currentRightPosition] = LPS[currentLeftPosition];
                
                } else if(diff == LPS[currentLeftPosition] && centerRightPosition == (lenOfPosition - 1)) {
                    //case 2
                    // B 跟 C 沒有超出 A 範圍的可能性
                    // center palindrome is suffix of input string
                
                    LPS[currentRightPosition] = LPS[currentLeftPosition];
                
                } else if(diff == LPS[currentLeftPosition] && centerRightPosition < (lenOfPosition - 1)) {
                    //case 3
                    //因為 A 並不是 input string 的後綴，所以 C 有延展的可能性
                    //  且 C 的長度至少跟 B 一樣長，所以可以從 B 的長度開始往左右遍尋
                
                    LPS[currentRightPosition] = LPS[currentLeftPosition];
                    expansion = 1;
                
                } else if(diff < LPS[currentLeftPosition]) {
                    //case 4
                    // B 的長度大於 A 右側最大的長度，所以 C 仍有延展的可能性
                    
                    LPS[currentRightPosition] = diff;
                    expansion = 1;
                
                }
            } else {
                /*cout << "centerPosition : " << centerPosition << endl;
                cout << "centerLeftPosition : " << centerLeftPosition << endl;
                cout << "centerRightPosition : " << centerRightPosition << endl;
                cout << "currentRightPosition : " << currentRightPosition << endl;
                cout << "currentLeftPosition : " << currentLeftPosition << endl;
                cout << "else!" << endl;*/
                
                LPS[currentRightPosition] = 0;
                expansion = 1;
            }
            
            if(expansion == 1) {
                while((((currentRightPosition + LPS[currentRightPosition]) < lenOfPosition) &&
                       ((currentRightPosition - LPS[currentRightPosition]) > 0)) &&
                      (((currentRightPosition + LPS[currentRightPosition] + 1) % 2 == 0) || 
                      s[(currentRightPosition + LPS[currentRightPosition] + 1)/2] == s[(currentRightPosition - LPS[currentRightPosition] - 1)/2])) {
                    LPS[currentRightPosition]++;
                }
            }
            
            if(LPS[currentRightPosition] > longestLPS) {
                longestLPS = LPS[currentRightPosition];
                longestCenterPosition = currentRightPosition;
            }
            
            /*cout << "currentRightPosition : " << currentRightPosition << endl;
            cout << "LPS[currentRightPosition] : " << LPS[currentRightPosition] << endl;*/
            
            if(currentRightPosition + LPS[currentRightPosition] > centerRightPosition) {
                centerPosition = currentRightPosition;
                centerRightPosition = centerPosition + LPS[centerPosition];
            }
            
        }
        
        //cout << "longestLPS : " << longestLPS << ", longestCenterPosition : " << longestCenterPosition << endl;  
        
        return s.substr((longestCenterPosition-longestLPS)/2, longestLPS);
    }
};
