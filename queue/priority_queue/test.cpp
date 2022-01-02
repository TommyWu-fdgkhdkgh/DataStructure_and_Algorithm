#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;

int main() {

  /*priority_queue<int, vector<int>, greater<int>> pq;

  pq.push(1);
  pq.push(2);
  pq.push(3);

  while(!pq.empty()) {
    cout << pq.top() << endl;
    pq.pop();
  }*/

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

  pq.push(make_pair(3, 1));
  pq.push(make_pair(1, 3));
  pq.push(make_pair(2, 2));

  while(!pq.empty()) {
    pair<int, int> now = pq.top();
    pq.pop();

    printf("first : %d, second: %d\n", now.first, now.second);

  }

  cout << "hi" << endl;

  return 0;
}
