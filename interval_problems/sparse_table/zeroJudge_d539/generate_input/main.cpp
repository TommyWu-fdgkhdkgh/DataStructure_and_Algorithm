#include <iostream>

using namespace std;

#define MAX 200000 

int main() {
   cout << MAX << endl;

   srand(time (NULL));

   for(int i = 0;i < MAX;i++) {
      cout << (int) rand();
      if(i != MAX - 1) {
         cout << " ";
      }
   }
   cout << endl;

   cout << MAX << endl;
   for(int i = 0;i < MAX;i++) {
      cout << (((int)rand()) % MAX) + 1 << " " << (((int)rand()) % MAX) + 1 << endl;
   }

   return 0;
}
