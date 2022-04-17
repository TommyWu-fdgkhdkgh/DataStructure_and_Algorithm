#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int lookUp(vector<int> &input, vector<int> &block, int l, int r, int k) {
   
   int res = 0;

   for(int i = l;i <= r;) {
      if(i % k == 0 && i + k <= r) {
         res = max(res, block[i / k]);
         i += k;
      } else {
         res = max(res, input[i]);
         i++;
      }
   }

   return res;
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

   int k = sqrt(input.size());

   // num of blocks
   int nb = input.size() / k;
   if(input.size() % k != 0) {
      nb++;
   }

   vector<int> block = vector<int>(nb, 0); 
   for(int i = 0;i < input.size();i++) {
       block[i / k] = max(input[i], block[i / k]);
   }

   for(int i = 0;i < n;i++) {
      int a, b;
      cin >> st;
      a = atoi(st.c_str());
      cin >> st;
      b = atoi(st.c_str());

      int left = min(a, b) - 1;
      int right = max(a, b) - 1;
    
      int ans = lookUp(input, block, left, right, k);
      cout << ans << endl;
   }

   return 0;
}
