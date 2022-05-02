#include <cstdio>
#include <iostream>
#include <vector>

#define LOWBIT(x) (x & -x)

using namespace std;

void __modify(int pos, int diff, vector<int> &bit) {
    for(;pos < bit.size();pos += LOWBIT(pos)) {
      bit[pos] += diff;
   }
}

void modify(int pos, int val, vector<int> &orig, vector<int> &bit) {
   int diff = val - orig[pos];
   pos += 1;
   __modify(pos, diff, bit);
}

int query(int pos, vector<int> &bit) {
   pos += 1;
   int res = 0;
   for(;pos >= 1;pos -= LOWBIT(pos)) {
      res += bit[pos];
   }
   return res;
}

void initialize(vector<int> &orig, vector<int> &bit) {
   for(int i = 0;i < orig.size();i++) {
      __modify(i + 1, orig[i], bit);
   }   
}

int main(int argc, char *argv[]) {
   // printf("%d\n", LOWBIT(8));
   // printf("%d\n", LOWBIT(10));

   vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   vector<int> bit = vector<int>(v.size() + 1, 0);

   initialize(v, bit);

   printf("%d\n", query(8, bit));

   return 0;
}
