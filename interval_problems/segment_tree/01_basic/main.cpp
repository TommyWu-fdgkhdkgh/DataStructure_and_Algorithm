#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void build_segment_tree(int left, int right, int vertex,
                        vector<int> &segment_tree,
                        vector<int> &input) {

   if(left == right) {
      segment_tree[vertex] = input[left];
      return;
   }

   int mid = (left + right) / 2;
   build_segment_tree(left, mid, vertex * 2 + 1,
                      segment_tree, input);
   build_segment_tree(mid + 1, right, vertex * 2 + 2,
                      segment_tree, input);

   segment_tree[vertex] = max(segment_tree[vertex * 2 + 1],
                              segment_tree[vertex * 2 + 2]);
}

void modifyOnePoint(int l, int r, int pos, int vertex, int value,
                     vector<int> &segment_tree) {
   if(l == r) {
      segment_tree[vertex] = value;
      return;
   }

   int mid = (l + r) / 2;
   if(pos <= mid) {
      modifyOnePoint(l, mid, pos, vertex, value,
                      segment_tree);
   } else {
      modifyOnePoint(mid + 1, r, pos, vertex, value,
                      segment_tree);
   }

   segment_tree[vertex] = max(segment_tree[vertex * 2 + 1],
                              segment_tree[vertex * 2 + 2]);
}

int lookUpInterval(int nowL, int nowR, int vertex,
                     int lookUpL, int lookUpR,
                     vector<int> &segment_tree) {

   if(nowL == lookUpL && nowR == lookUpR) {
      return segment_tree[vertex];
   }

   int mid = (nowL + nowR) / 2;

   if(lookUpR <= mid) {
      return lookUpInterval(nowL, mid, vertex * 2 + 1,
                             lookUpL, lookUpR, segment_tree);
   } else if(lookUpL > mid) {
      return lookUpInterval(mid + 1, nowR, vertex * 2 + 2,
                             lookUpL, lookUpR, segment_tree);
   } else {
      int result = lookUpInterval(nowL, mid, vertex * 2 + 1,
                                   lookUpL, mid, segment_tree);
      result = max(result, lookUpInterval(mid + 1, nowR, vertex * 2 + 2,
                                           mid + 1, lookUpR, segment_tree));
      return result;
   }
   return 0;
}

int main(int argc, char *argv[]) {
   int n;
   cin >> n;

   vector<int> input(n, 0);

   // Q: 請證明為什麼 4 * n 的位置夠用
   vector<int> segment_tree(4 * n, 0);

   for(int i = 0;i < n;i++) {
      cin >> input[i];
   }

   build_segment_tree(0, n - 1, 0, segment_tree, input);

   cin >> n;

   for(int i = 0;i < n;i++) {
      int a, b;
      cin >> a;
      cin >> b;

      int left = min(a, b) - 1;
      int right = max(a, b) - 1;

      printf("%d\n", lookUpInterval(0, input.size() - 1, 0,
                                    left, right, segment_tree));
   }
   return 0;
}
