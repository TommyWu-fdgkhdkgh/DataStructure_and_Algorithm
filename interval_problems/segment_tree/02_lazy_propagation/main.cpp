#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void build_segment_tree(int left, int right, int vertex,
                        vector<vector<int>> &segment_tree,
                        vector<int> &input) {

   if(left == right) {
      segment_tree[vertex][0] = input[left];
      return;
   }

   int mid = (left + right) / 2;
   build_segment_tree(left, mid, vertex * 2 + 1,
                      segment_tree, input);
   build_segment_tree(mid + 1, right, vertex * 2 + 2,
                      segment_tree, input);

   segment_tree[vertex][0] = max(segment_tree[vertex * 2 + 1][0],
                                 segment_tree[vertex * 2 + 2][0]);
}



void modifyInterval(int nowl, int nowr, int modifyL, int modifyR, 
                    int vertex, int val, vector<vector<int>> &segment_tree) {

   // Q: 區間加法需要這個步驟，但區間設值好像就不用這一步了 ? 
   // 在線段樹內的區間 [nowl, nowr] 含有懶人標記 
   // 1. 先將懶人標記清除掉，並更新 [nowl, nowr] 的值
   // 2. 更新子節點的懶人標記的值
   if(segment_tree[vertex][1] == 1) {
      // 懶人標記內記錄了，之前這個區間被設定了什麼值
      segment_tree[vertex][0] = (nowr - nowl + 1) * segment_tree[vertex][2];
 
      if(nowl != nowr) {
         // 設定左子節點
         segment_tree[vertex * 2 + 1][1] = 1;
         segment_tree[vertex * 2 + 1][2] = segment_tree[vertex][2];

         // 設定右子節點
         segment_tree[vertex * 2 + 2][1] = 1;
         segment_tree[vertex * 2 + 2][2] = segment_tree[vertex][2];
              
         segment_tree[vertex][1] = 0;
      }
   }

   // 找到完全符合的區間
   if(nowl == modifyL && nowr == modifyR) {
      segment_tree[vertex][0] = (nowr - nowl + 1) * val;

      // left
      segment_tree[vertex * 2 + 1][1] = 1;
      segment_tree[vertex * 2 + 1][2] = val;

      // right
      segment_tree[vertex * 2 + 2][1] = 1;
      segment_tree[vertex * 2 + 2][2] = val;

      return;
   }

   int mid = (nowl + nowr) / 2;
   if (modifyR <= mid) {
      modifyInterval(nowl, mid, modifyL, modifyR, vertex * 2 + 1, val, segment_tree);
   } else if(modifyL > mid) {
      modifyInterval(mid + 1, nowr, modifyL, modifyR, vertex * 2 + 1, val, segment_tree);
   } else {
      modifyInterval(nowl, mid, modifyL, mid, vertex * 2 + 1, val, segment_tree);
      modifyInterval(mid + 1, nowr, mid + 1, modifyR, vertex * 2 + 1, val, segment_tree);
   }

   segment_tree[vertex][0] = max(segment_tree[vertex * 2 + 1][0], segment_tree[vertex * 2 + 2][0]);

}

int lookUpInterval(int nowl, int nowr, int vertex,
                     int lookUpL, int lookUpR,
                     vector<vector<int>> &segment_tree) {

   // Q: 區間加法需要這個步驟，但區間設值好像就不用這一步了 ? 
   // 在線段樹內的區間 [nowl, nowr] 含有懶人標記 
   // 1. 先將懶人標記清除掉，並更新 [nowl, nowr] 的值
   // 2. 更新子節點的懶人標記的值
   if(segment_tree[vertex][1] == 1) {
      printf("fdgk 1\n");
      // 懶人標記內記錄了，之前這個區間被設定了什麼值
      segment_tree[vertex][0] = (nowr - nowl + 1) * segment_tree[vertex][2];
 
      if(nowl != nowr) {
         // 設定左子節點
         segment_tree[vertex * 2 + 1][1] = 1;
         segment_tree[vertex * 2 + 1][2] = segment_tree[vertex][2];

         // 設定右子節點
         segment_tree[vertex * 2 + 2][1] = 1;
         segment_tree[vertex * 2 + 2][2] = segment_tree[vertex][2];
              
         segment_tree[vertex][1] = 0;
      }
   }

   // 找到完全符合的區間
   if(nowl == lookUpL && nowr == lookUpR) {
      return segment_tree[vertex][0];
   }

   int mid = (nowl + nowr) / 2;
   if(lookUpR <= mid) {
      return lookUpInterval(nowl, mid, vertex * 2 + 1,
                     lookUpL, lookUpR,
                     segment_tree);
   } else if(lookUpL > mid) {
      return lookUpInterval(mid + 1, nowr, vertex * 2 + 2,
                     lookUpL, lookUpR,
                     segment_tree);
   } else {
      int res = 0;
      res = lookUpInterval(nowl, mid, vertex * 2 + 1,
                            lookUpL, mid,
                            segment_tree);

      res = max(res, lookUpInterval(mid + 1, nowr, vertex * 2 + 2,
                                    mid + 1, lookUpR,
                                    segment_tree));
      return res;
   }   

   return 0;
}

int main(int argc, char *argv[]) {
   int n;
   cin >> n;

   vector<int> input(n, 0);

   // Q: 請證明為什麼 4 * n 的位置夠用
   // segment_tree[i][0] : value
   // segment_tree[i][1] : 0 --> don't have lazy tag, 1 --> have lazy tag
   // segment_tree[i][2] : value of lazy tag
   vector<vector<int>> segment_tree(4 * n, vector<int>(3, 0));

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
