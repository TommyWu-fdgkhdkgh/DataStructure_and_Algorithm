#include <cstdio>


int quickPow(int base, int n) {
   int res = 1;

   while(n > 0) {
      if(n & 1) {
         res *= base;     
      }
      base *= base;
      n = n >> 1;
   }

   return res;
}

int main(int argc, char *argv[]) {
   printf("quickPow : %d\n", quickPow(2, 10));

   return 0;
}
