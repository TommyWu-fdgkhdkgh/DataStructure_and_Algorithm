#include <iostream>
#include <vector>
#include <cstring>


typedef struct Node Node;
struct Node {
   unsigned long long val;
   bool isLazy;
   unsigned long long lazyTag;
};

using namespace std;

void build_segment_tree(int nowL, int nowR, int vertex, 
                        vector<Node> &segment_tree, vector<unsigned long long> &input) {
  if(nowL == nowR) {
    segment_tree[vertex].val = input[nowL];
    return;
  }

  int nowM = (nowL + nowR) / 2;
  build_segment_tree(nowL, nowM, vertex * 2 + 1,
                     segment_tree, input);

  build_segment_tree(nowM + 1, nowR, vertex * 2 + 2,
                     segment_tree, input);

  segment_tree[vertex].val = segment_tree[vertex * 2 + 1].val + segment_tree[vertex * 2 + 2].val;
}

void modify(int nowL, int nowR, int modifyL, int modifyR, int vertex, unsigned long long val,
            vector<Node> &segment_tree) {
   
   if(segment_tree[vertex].isLazy) {
      segment_tree[vertex].val += (nowR - nowL + 1) * segment_tree[vertex].lazyTag;
   
      
      if(nowL != nowR) { // fix, prevent segment fault
        segment_tree[vertex * 2 + 1].isLazy = true;
        segment_tree[vertex * 2 + 1].lazyTag += segment_tree[vertex].lazyTag;

        segment_tree[vertex * 2 + 2].isLazy = true;
        segment_tree[vertex * 2 + 2].lazyTag += segment_tree[vertex].lazyTag;
      } // fix

      segment_tree[vertex].isLazy = false;
      segment_tree[vertex].lazyTag = 0;
   }

   if(nowL == modifyL && nowR == modifyR) {

      segment_tree[vertex].val += (nowR - nowL + 1) * val;

      if(nowL != nowR) { // fix, prevent segment fault
        segment_tree[vertex * 2 + 1].isLazy = true;
        segment_tree[vertex * 2 + 1].lazyTag += val;

        segment_tree[vertex * 2 + 2].isLazy = true;
        segment_tree[vertex * 2 + 2].lazyTag += val;
      } // fix
      return;
   }

   int nowM = (nowL + nowR) / 2; 
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

   segment_tree[vertex].val = segment_tree[vertex * 2 + 1].val + segment_tree[vertex * 2 + 2].val;
}

unsigned long long lookUp(int nowL, int nowR, int lookUpL, int lookUpR, int vertex,
           vector<Node> &segment_tree) {

  if(segment_tree[vertex].isLazy) {
    segment_tree[vertex].val += (nowR - nowL + 1) * segment_tree[vertex].lazyTag;
   
    if(nowL != nowR) { // fix, prevent segment fault
      segment_tree[vertex * 2 + 1].isLazy = true;
      segment_tree[vertex * 2 + 1].lazyTag += segment_tree[vertex].lazyTag;

      segment_tree[vertex * 2 + 2].isLazy = true;
      segment_tree[vertex * 2 + 2].lazyTag += segment_tree[vertex].lazyTag;
    } // fix
    segment_tree[vertex].isLazy = false;
    segment_tree[vertex].lazyTag = 0;
  }

  if(nowL == lookUpL && nowR == lookUpR) {
    return segment_tree[vertex].val;    
  }

  int nowM = (nowL + nowR) / 2;
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
  vector<Node> segment_tree = vector<Node>(4 * input_len);
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
       int left, right, val;
       cin >> left;
       cin >> right;
       cin >> val;

       left--;  
       right--;

       modify(0, input.size() - 1, left, right, 0, val,
              segment_tree);
    } else if(op == 2) {
       int left, right;
       cin >> left;
       cin >> right;
       left--;
       right--;

       unsigned long long res = lookUp(0, input.size() - 1, left, right, 0,
                          segment_tree);
       cout << res << endl;
    }
  }
/*
  for(int i = 0;i < input.size();i++) {
    printf("input[%d] : %llu\n", i, input[i]);
  }
  for(int i = 0;i < segment_tree.size();i++) {
    printf("segment_tree[%d].val : %llu\n", i, segment_tree[i].val);
  }
*/
  return 0;
}
