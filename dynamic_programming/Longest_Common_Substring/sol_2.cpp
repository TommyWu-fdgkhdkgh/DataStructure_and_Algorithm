// 題目網址 ： https://leetcode.com/problems/maximum-length-of-repeated-subarray/
// time : O(n*m)
// space : O(1)

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        
        int counter;
        int max;
        max = -1e9;
        for(int i = 0;i < A.size();i++) {
            int tempi = i;
            counter = 0;
            for(int j = 0;j < B.size() && tempi < A.size();j++, tempi++) {
                if(A[tempi] == B[j]) {
                    //printf("hihi! tempi : %d, j : %d\n", tempi, j);
                    counter++;
                } else {
                    if(counter > max) {
                        //printf("he! counter = %d\n", counter);
                        max = counter;
                    }
                    counter = 0;
                }
            }
            if(counter > max) {
                max = counter;
            }
        }
        
        for(int i = 0;i < B.size();i++) {
            int tempi = i;
            counter = 0;
            //max = -1e9;
            for(int j = 0;j < A.size() && tempi < B.size();j++, tempi++) {
                if(B[tempi] == A[j]) {
                    counter++;
                } else {
                    if(counter > max) {
                        max = counter;
                    }
                    counter = 0;
                }
            }
            if(counter > max) {
                max = counter;
            }
        }
        
        return max;
        
    }
};
