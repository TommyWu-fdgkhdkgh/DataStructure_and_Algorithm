#include <cstdio>
#include <iostream>
#include <vector>

#define LL long long
#define LOWBIT(x) (x & -x)

using namespace std;

void __modify(LL pos, LL diff, vector<LL> &bit) {
   for(;pos < bit.size();pos += LOWBIT(pos)) {
      bit[pos] += diff;
   }
}

void modify(LL pos, LL diff, vector<LL> &bit) {
   pos += 1;   
   __modify(pos, diff, bit);  
}

void interval_modify(LL left, LL right, LL val, vector<LL> &dv, vector<LL> &dv2, vector<LL> &bitdv, vector<LL> &bitdv2) {
   modify(left, val, bitdv);
   modify(left, (dv[left] + val) * (left + 1) - dv2[left], bitdv2);
   if(right + 1 < dv.size()) {
      modify(right + 1, -1 * val, bitdv);
      modify(right + 1, (right + 2) * (dv[right + 1] - val) - dv2[right + 1], bitdv2);
   }

   dv[left] += val;
   dv2[left] = (left + 1) * dv[left];

   if(right + 1 < dv.size()) {
      dv[right + 1] -= val;
      dv2[right + 1] = (right + 2) * dv[right + 1];
   }
}

LL query(LL pos, vector<LL> &bit) {
   pos += 1;
   LL res = 0;
   for(;pos >= 1;pos -= LOWBIT(pos)) {
      res += bit[pos];
   } 
   return res;
}

LL interval_sum(LL left, LL right, vector<LL> &bitdv, vector<LL> &bitdv2) {
   LL res = 0;
  
   LL sumLeft1 = 0;
   LL sumLeft2 = 0;
   if(left > 0) {
      sumLeft1 = query(left - 1, bitdv);
      sumLeft2 = query(left - 1, bitdv2);
   } 

   LL sumRight1 = query(right, bitdv);
   LL sumRight2 = query(right, bitdv2);
   
   // left 原本是 0-indexed, 
   //   + 1 後變成 1-indexed
   //   再 + 1 使其變成 x + 1
   LL sumLeft = sumLeft1 * (left - 1 + 2) - sumLeft2;
   LL sumRight = sumRight1 * (right + 2) - sumRight2; 

   res = sumRight - sumLeft;

   return res;
}

int main(int argc, char *argv[]) {
   LL n;
   cin >> n;
   // printf("%lld\n", n);
   vector<LL> inv = vector<LL>(n);

   for(int i = 0;i < n;i++) {
      cin >> inv[i];  
   }

   vector<LL> dv  = vector<LL>(inv.size(), 0);
   vector<LL> dv2 = vector<LL>(inv.size(), 0);
  
   dv[0] = inv[0];
   dv2[0] = inv[0];
   for(int i = 1;i < n;i++) {
      dv[i] = inv[i] - inv[i - 1];
      dv2[i] = dv[i] * (i + 1); 
   }

   vector<LL> bitdv  = vector<LL>(inv.size() + 1, 0);
   vector<LL> bitdv2 = vector<LL>(inv.size() + 1, 0);

   // initialize bit
   for(int i = 0;i < inv.size();i++) {
      modify(i, dv[i], bitdv);
      modify(i, dv2[i], bitdv2);
   }

   cin >> n;
   for(int i = 0;i < n;i++) {
      int op;
      cin >> op;
      if(op == 1) {
         LL left;
         LL right;
         LL val;

         cin >> left;
         cin >> right;
         cin >> val; 
    
         left -= 1;
         right -= 1;

         interval_modify(left, right, val, dv, dv2, bitdv, bitdv2);
      } else if(op == 2) {
         LL left;
         LL right;
 
         cin >> left;
         cin >> right;

         left -= 1;
         right -= 1;

         LL res = interval_sum(left, right, bitdv, bitdv2);
         printf("%lld\n", res);
      }
   }

   return 0;
}
