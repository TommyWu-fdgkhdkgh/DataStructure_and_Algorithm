#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void initialize_sparse_table(vector<int> &input, vector<vector<int>> &sparse_table, 
                             int start, int log_2_len) {
   // log_2_len = log_2(len)
   int len = pow(2, log_2_len);
   int pow2 = pow(2, log_2_len - 1);

   if(start >= input.size()) {
      return;
   }

   if(log_2_len == 0) {
      sparse_table[start][0] = input[start];
      return;
   }   

   if(sparse_table[start][log_2_len] != 0) {
      return;
   }


   initialize_sparse_table(input, sparse_table, 
                           start, log_2_len - 1);

   if(start + pow2 < input.size()) {
      initialize_sparse_table(input, sparse_table, 
                              start + pow2, log_2_len - 1);
   }

   if(start + pow2 < input.size()) {
      sparse_table[start][log_2_len] = max(sparse_table[start][log_2_len - 1], 
                                           sparse_table[start + pow2][log_2_len - 1]);
   } else {
      sparse_table[start][log_2_len] = sparse_table[start][log_2_len - 1];
   } 

}


int lookUp(vector<vector<int>> &sparse_table, int left, int right) {
   int len = right - left + 1;   
   int log_2_len = 0;
   int tmp = 1;
   while(tmp < len) {
      tmp *= 2;
      if(tmp < len) {
         log_2_len++;
      }
   }

   cout << "left : " << left << ", right : " << right << ", right - pow(2, log_2_len) + 1 : " << right - pow(2, log_2_len) + 1 << endl;
   cout << "log_2_len : " << log_2_len << endl;

   return max(sparse_table[left][log_2_len], sparse_table[right - pow(2, log_2_len) + 1][log_2_len]);
}

int main(int argc, char *argv[]) {
   
   string st;
   cin >> st;

   int n = atoi(st.c_str());
   vector<int> input;
   for(int i = 0;i < n;i++) {
      cin >> st;
      input.push_back(atoi(st.c_str()));
   }

   cin >> st;
   n = atoi(st.c_str());

   int cols = 0;
   int tmp = 1;
   while(tmp < input.size()) { 
      cols++;
      tmp *= 2;
   }
   cols++;

   vector<vector<int>> sparse_table = vector<vector<int>>(tmp, vector<int>(cols, 0));

   for(int i = 1;i < sparse_table[0].size();i++) {
      for(int j = 0;j < sparse_table.size();j++) {
         initialize_sparse_table(input, sparse_table, j, i);
      }
   }

   for(int i = 0;i < sparse_table[0].size();i++) {
      for(int j = 0;j < sparse_table.size();j++) {
         cout << "j : " << j << ", i : " << i << ", sparse_table[" << j << "][" << i << "]" << " : " << sparse_table[j][i] << endl;
      }
   }


   for(int i = 0;i < n;i++) {
      int a, b;
      cin >> st;
      a = atoi(st.c_str());
      cin >> st;
      b = atoi(st.c_str());

      int ans = lookUp(sparse_table, a - 1, b - 1);
      cout << ans << endl;
   }

   return 0;
}
