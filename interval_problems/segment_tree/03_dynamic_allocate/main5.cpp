#include <iostream>
#include <vector>
#include <cstring>

typedef struct Node Node;
struct Node {
   unsigned long long val;
   unsigned long long lazyTag;
};

using namespace std;

void build_segment_tree(unsigned long long nowL, unsigned long long nowR, unsigned long long vertex, 
                        vector<Node> &segment_tree, vector<unsigned long long> &input) {
  if(nowL == nowR) {
    segment_tree[vertex].val = input[nowL];
    return;
  }

  unsigned long long nowM = (nowL + nowR) / 2;
  build_segment_tree(nowL, nowM, vertex * 2 + 1,
                     segment_tree, input);

  build_segment_tree(nowM + 1, nowR, vertex * 2 + 2,
                     segment_tree, input);

  segment_tree[vertex].val = segment_tree[vertex * 2 + 1].val + segment_tree[vertex * 2 + 2].val;
}

void modify(unsigned long long nowL, unsigned long long nowR, unsigned long long modifyL, unsigned long long modifyR, 
            unsigned long long vertex, unsigned long long val,
            vector<Node> &segment_tree) {
   
   if(segment_tree[vertex].lazyTag != 0) {
      segment_tree[vertex].val += (nowR - nowL + 1) * segment_tree[vertex].lazyTag;

      if(nowL != nowR) { // fix, prevent segment fault
        segment_tree[vertex * 2 + 1].lazyTag += segment_tree[vertex].lazyTag;

        segment_tree[vertex * 2 + 2].lazyTag += segment_tree[vertex].lazyTag;
      } // fix

      segment_tree[vertex].lazyTag = 0;
   }


   // 最主要就是這行，讓我 AC 的 !!??
   // segment_tree[vertex].val += (modifyR - modifyL + 1) * val;

   if(nowL == modifyL && nowR == modifyR) {
      segment_tree[vertex].val += (modifyR - modifyL + 1) * val;

      if(nowL != nowR) { // fix, prevent segment fault
        segment_tree[vertex * 2 + 1].lazyTag += val;
        segment_tree[vertex * 2 + 2].lazyTag += val;
      } // fix
      return;
   }

   unsigned long long nowM = (nowL + nowR) / 2; 
   if(modifyR <= nowM) {
      modify(nowL, nowM, modifyL, modifyR, vertex * 2 + 1, val,
             segment_tree);
   } else if(modifyL > nowM) {
      modify(nowM + 1, nowR, modifyL, modifyR, vertex * 2 + 2, val, 
             segment_tree);
   } else {
      modify(nowL, nowM, modifyL, nowM, vertex * 2 + 1, val,
             segment_tree);

      modify(nowM + 1, nowR, nowM + 1, modifyR, vertex * 2 + 2, val,
             segment_tree);
   }

   // 這裡會有個問題，那就是在修改的過程中，我們並不會遍尋所有該節點的子節點
   //   所以有可能該節點的子節點的懶人標記還沒展開
   //   導致其 segment_tree[vertex * 2 + 1 | vertex * 2 + 2].val 是舊的值
   segment_tree[vertex].val =  segment_tree[vertex * 2 + 1].val + segment_tree[vertex * 2 + 1].lazyTag * (nowM - nowL + 1);
   segment_tree[vertex].val += segment_tree[vertex * 2 + 2].val + segment_tree[vertex * 2 + 2].lazyTag * (nowR - (nowM + 1) + 1);
}

unsigned long long lookUp(unsigned long long  nowL, unsigned long long  nowR, 
           unsigned long long lookUpL, unsigned long long lookUpR, unsigned long long vertex,
           vector<Node> &segment_tree) {

   if(segment_tree[vertex].lazyTag != 0) {
      segment_tree[vertex].val += (nowR - nowL + 1) * segment_tree[vertex].lazyTag;

      if(nowL != nowR) { // fix, prevent segment fault
        segment_tree[vertex * 2 + 1].lazyTag += segment_tree[vertex].lazyTag;

        segment_tree[vertex * 2 + 2].lazyTag += segment_tree[vertex].lazyTag;
      } // fix

      segment_tree[vertex].lazyTag = 0;
   }

  if(nowL == lookUpL && nowR == lookUpR) {
    return segment_tree[vertex].val;    
  }

  unsigned long long nowM = (nowL + nowR) / 2;
  if(lookUpR <= nowM) {
    return lookUp(nowL, nowM, lookUpL, lookUpR, vertex * 2 + 1,
                  segment_tree);
  } else if(lookUpL > nowM) {
    return lookUp(nowM + 1, nowR, lookUpL, lookUpR, vertex * 2 + 2,
                  segment_tree);
  } 
  unsigned long long res = lookUp(nowL, nowM, lookUpL, nowM, vertex * 2 + 1,
                   segment_tree);

  res += lookUp(nowM + 1, nowR, nowM + 1, lookUpR, vertex * 2 + 2,
                segment_tree);
 
  return res;
}

int main(int argc, char *argv[]) {

  int input_len;
  cin >>  input_len;
  vector<unsigned long long> input(input_len);
  vector<Node> segment_tree = vector<Node>(6 * input_len);
  for(int i = 0;i < segment_tree.size();i++) {
    memset(&(segment_tree[i]), 0, sizeof(Node));
  }
 
  for(int i = 0;i < input_len;i++) {
    cin >> input[i];
  }

  build_segment_tree(0, input.size() - 1, 0, 
                     segment_tree, input);

  int num_of_op;
  cin >> num_of_op;

  for(int i = 0;i < num_of_op;i++) {
    int op;
    cin >> op;
    if(op == 1) {
       unsigned long long  left, right, val;
       cin >> left;
       cin >> right;
       cin >> val;

       left--;  
       right--;

       modify(0, input.size() - 1, left, right, 0, val,
              segment_tree);
    } else if(op == 2) {
       unsigned long long  left, right;
       cin >> left;
       cin >> right;
       left--;
       right--;

       unsigned long long res = lookUp(0, input.size() - 1, left, right, 0,
                          segment_tree);
       cout << res << endl;
    }
  }

  return 0;
}
