// 題目網址：https://practice.geeksforgeeks.org/problems/longest-common-substring/0
// time : O(N^2),
// space : O(1) 
// 來源 ： 我

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;


int main() {

  int num_of_test;
  int len1, len2;
  string st1, st2;

  cin >> num_of_test;

  int max = -1e9;

  for(int i = 0;i < num_of_test;i++) {
    max = -1e9;

    cin >> len1 >> len2;
    cin >> st1;
    cin >> st2;
    //cout << st1 << endl;
    //cout << st2 << endl;

    /*if(len2 > len1) {
      string tempst = st1;
      st1 = st2;
      st2 = tempst;

      int tempint = len1;
      len1 = len2;
      len2 = tempint;
    }*/


    int counter;
    for(int i = 0;i < len1;i++) {
      counter = 0;
      int tempi = i;
      for(int j = 0;j < len2 && tempi < len1;j++, tempi++) {
        if(st1[tempi] == st2[j]) {
          //printf("st1[tempi] = %c, st2[j] = %c\n", st1[tempi], st2[j]);
          counter++;
        } else {
          if(counter > max) {
            cout << "common : " << st1.substr(tempi, counter) << endl;
            max = counter;
          }
          counter = 0;
        } 
      }
      if(counter > max) {
        max = counter;
      }
    } 
    for(int i = 0;i < len2;i++) {
      counter = 0;
      int tempi = i;
      for(int j = 0;j < len1 && tempi < len2;j++, tempi++) {
        if(st2[tempi] == st1[j]) {
          //printf("st1[tempi] = %c, st2[j] = %c\n", st1[tempi], st2[j]);
          counter++;
        } else {
          if(counter > max) {
            cout << "common : " << st2.substr(tempi, counter) << endl;
            max = counter;
          }
          counter = 0;
        } 
      }
      if(counter > max) {
        max = counter;
      }
    } 

    cout << "ans : " << max << endl;
  }
  return 0;
}
