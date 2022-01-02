// 題目敘述有點糟
//   學到了新的名詞 ： Digital root （https://en.wikipedia.org/wiki/Digital_root）

class Solution {
public:
    int addDigits(int num) {
        int temp = num;
        int oritemp = num;
        int next = 0;
        
        if(num == 0) {
            return 0;
        }
        
        
        while(1){
            while(temp > 0) {
                next += temp % 10;
                temp/=10;
            }
            
            if(oritemp == next) {
                return oritemp;   
            }
            
            if(next < 10 && __builtin_popcount(next) == 1) {
                return next; 
            }
            
            
            
            temp = next;
            oritemp = next;
            next = 0;
        }
        
        return 0;    }
};
