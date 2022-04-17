#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

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


int lookUp(vector<int> &input, vector<vector<int>> &sparse_table, int left, int right) {
   int len = right - left + 1;   
   int log_2_len = 0;
   int tmp = 1;

   log_2_len = log2(len);
   int pow2 = pow(2, log_2_len);

   return max(sparse_table[left][log_2_len], sparse_table[right - pow2 + 1][log_2_len]);
}

int main(int argc, char *argv[]) {
   
   string st;
   cin >> st;

   int n = atoi(st.c_str());
   vector<int> input = vector<int>(n);
   for(int i = 0;i < n;i++) {
      int t;
      scanf("%d", &t);
      input[i] = t;
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

   vector<vector<int>> sparse_table = vector<vector<int>>(input.size() + 1, vector<int>(cols, 0));

   for(int i = 1;i < sparse_table[0].size();i++) {
      for(int j = 0;j < input.size();j++) {
         initialize_sparse_table(input, sparse_table, j, i);
      }
   }

   for(int i = 0;i < n;i++) {
      int a, b;
      scanf("%d %d", &a, &b);

      int left = min(a, b);
      int right = max(a, b);

      int ans = 0;
      ans = lookUp(input, sparse_table, left - 1, right - 1);
      cout << ans << endl;
   }

   return 0;
}
