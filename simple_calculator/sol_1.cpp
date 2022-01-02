// 題目 ： https://leetcode.com/problems/basic-calculator-ii/
//   這一題不需要處理小括號，所以理論上應該挺簡單的，但是我卻還是寫了很久...
//   我好廢呀QQQ

//   state machine


class Solution {
public:
    
    /*
        因為是簡單的計算機，所以只需要注意 '*', '/' 這想種符號即可
    */
    
    /*
    state machine
        
    
    
    */
    
    int calculate(string s) {
        
        int number_register;
        int number_register2;
        char calcu_register = 0;
        char calcu_register2 = 0;
        
        string st_number_register;
        int state = 1;
        
        int total;
        
        //stoi(number_register);
        
        for(int i = 0;i < s.size();i++) {
            if(s[i] == ' ') {
                continue;
            }
            
            if(state == 1) {
                // 初始狀態
                
                if(s[i] >= '0' && s[i] <= '9') {
                    st_number_register += s[i]; 
                } else if(s[i] == '+' || s[i] == '-') {
                    state = 2;
                    
                    number_register = stoi(st_number_register);
                    st_number_register = "";
                    calcu_register = s[i];
                } else if(s[i] == '*' || s[i] == '/' ) {
                    state = 3;
                                
                    number_register2 = stoi(st_number_register);
                    st_number_register = "";
                    calcu_register2 = s[i];
                }
            } else if(state == 2) {
                // 初始狀態收到 +, - 符號，要看下一個符號是 +, - 或是 *, /
                //   下一個符號若是 +, - ， 把前面的值清算一下，狀態不變
                //   下一個符號若是 *, / 進入狀態 4
                
                if(s[i] >= '0' && s[i] <= '9') {
                    st_number_register += s[i];
                } else if(s[i] == '+' || s[i] == '-') {
                    int temp = stoi(st_number_register);
                    
                    if(calcu_register == '+') {
                        total = number_register + temp;
                    } else if (calcu_register == '-') {
                        total = number_register - temp;
                    } else if(calcu_register == 0){
                
                    } else {
                        cout << "ERROR!" << endl;
                    }
                    
                    number_register = total;
                    calcu_register = s[i];
                    st_number_register = "";
                    
                } else if(s[i] == '*' || s[i] == '/') {
                    state = 4;
                    
                    //cout << "number_register2 : " << number_register2 << endl;
                    number_register2 = stoi(st_number_register);
                    st_number_register = "";
                    calcu_register2 = s[i];
                }
                
            } else if(state == 3) {
                // 初始狀態收到 *, / 符號，不用看下一個符號
                //   下一個符號若是 *, / 則持續在 3
                //   下一個符號若是 +, - 則回到 2
                
                if(s[i] >= '0' && s[i] <= '9') {
                    st_number_register += s[i];
                } else if(s[i] == '+' || s[i] == '-') {
                    int temp = stoi(st_number_register);
                    
                    if(calcu_register2 == '*') {
                        total = number_register2 * temp;
                    } else if(calcu_register2 == '/') {
                        total = number_register2 / temp;
                    } else if(calcu_register2 == 0){
                
                    } else {
                        cout << "ERROR!" << endl;
                    }
                    
                    number_register = total;
                    calcu_register = s[i];
                    st_number_register = "";
                    
                    state = 2;
                    
                } else if(s[i] == '*' || s[i] == '/') {
                    int temp = stoi(st_number_register);
                    
                    if(calcu_register2 == '*') {
                        total = number_register2 * temp;
                    } else if(calcu_register2 == '/') {
                        total = number_register2 / temp;
                    } else if(calcu_register2 == 0){
                
                    } else {
                        cout << "ERROR!" << endl;
                    }
                    
                    number_register2 = total;
                    calcu_register2 = s[i];
                    st_number_register = "";
                    
                }
                
                
            } else if(state == 4) {
                
                if(s[i] >= '0' && s[i] <= '9') {
                    st_number_register += s[i];
                } else if(s[i] == '+' || s[i] == '-') {
                    //清算前面的值，留在 state2
                    int temp = stoi(st_number_register);
                    
                    if(calcu_register2 == '*') {
                        total = number_register2 * temp;   
                    } else if(calcu_register2 == '/') {
                        //printf(" i : %d\n", i);
                        total = number_register2 / temp;
                    } else if(calcu_register2 == 0){
                
                    } else {
                        cout << "ERROR!" << endl;
                    }
                    //cout << "1_total  : " << total << endl;
                    
                    if(calcu_register == '+') {
                        total = number_register + total;
                    } else if(calcu_register == '-') {
                        //cout << "hi!" << endl;
                        
                        //cout << "2_total : " << total << endl;
                        
                        total = number_register - total; 
                    } else if(calcu_register == 0){
                
                    } else {
                        cout << "ERROR!" << endl;
                    }
                    
                    //cout << "i : " << i << ", total : " << total << endl;  
                    number_register = total;
                    calcu_register = s[i];
                    calcu_register2 = 0;
                    st_number_register = "";
                    state = 2;
                    
                } else if(s[i] == '*' || s[i] == '/') {
                    //清算前面的值，留在 state4
                    int temp = stoi(st_number_register);
                    
                    if(calcu_register2 == '*') {
                        //cout << "hi!" << endl;
                        total = number_register2 * temp;
                    } else if(calcu_register2 == '/') {
                        total = number_register2 / temp;
                    } else if(calcu_register2 == 0){
                        
                    } else {
                        cout << "ERROR!" << endl;
                    }
                    
                    number_register2 = total;
                    calcu_register2 = s[i];
                    st_number_register = "";
                }
                
            }
        }
        
        if(state == 1) {
            return stoi(st_number_register);
        } else if(state == 2) {
            if(calcu_register == '+') {
                return number_register + stoi(st_number_register);
            } else if(calcu_register == '-') {
                return number_register - stoi(st_number_register);
            } else if(calcu_register == 0){
                
            } else {
                cout << "ERROR!" << endl;
            }
        } else if(state == 3) {
            if(calcu_register2 == '*') {
                return number_register2 * stoi(st_number_register);
            } else if(calcu_register2 == '/') {
                return number_register2 / stoi(st_number_register);
            } else if(calcu_register2 == 0){
                
            } else {
                cout << "ERROR!" << endl;
            }
        } else if(state == 4) {
            int temp = stoi(st_number_register);            
        
            if(calcu_register2 == '*') {
                //cout << "!!" << endl;
                total = number_register2 * temp;
                //cout << "number_register2 : " << number_register2 << ", temp : " << temp << endl;
                //cout << "3_total : " << total << endl;
            } else if(calcu_register2 == '/') {
                total = number_register2 / temp;
            } else if(calcu_register2 == 0){
                
            } else {
                cout << "ERROR!" << endl;
            }
                    
            if(calcu_register == '+') {
                total = number_register + total;
            } else if(calcu_register == '-') {
                total = number_register - total; 
            } else if(calcu_register == 0) {
                
            } else {
                cout << "ERROR!" << endl;
            }
            
            return total;
        }
        
        
        return 0;
    }
};
