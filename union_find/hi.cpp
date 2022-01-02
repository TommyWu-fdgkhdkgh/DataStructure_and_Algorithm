#include <iostream>
#include <cstdlib>

using namespace std;

#define MAX_N 1000

int par[MAX_N];  //parents
int depth[MAX_N]; //depth of the tree

void init(int n) {
  for(int i = 0;i < n;i++){
    par[i] = i;
    depth[i] = 0;
  }
}

//在這個function，會讓depth改變吧
//但是書裡卻沒有處理這一塊的樣子，雖然也有說，為了簡化實作，所以會當作rank沒有改變
int find(int x) {
  if(par[x] == x){
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if(x == y) return;

  if(depth[x] < depth[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if(depth[x] == depth[y]) depth[x]++;
  }

}

bool same(int x, int y) {
  return find(x) == find(y);
}


int main() {


  cout << "hi" << endl;

  return 0;
}
