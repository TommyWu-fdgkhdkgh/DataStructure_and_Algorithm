#include <bits/stdc++.h>

using namespace std;

bool isCyclic(int V, vector<int> adj[]) {

  vector<bool> discover = vector<bool>(V, false);
  vector<bool> processed = vector<bool>(V, false);
  vector<int> parents = vector<int>(V, -1);
  queue<int> q;
  
  for(int i = 0;i < V;i++) {
    q.push(i);
    discover[i] = true;

    while(!q.empty) {

    }
  }  

   

  return false;
}

int main() {
  int t;
  cin >> t;

  while(t--) {
    int v, e;
    cin >> v >> e;

    vector<int> adj[v];

    for(int i = 0;i < e;i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
    }

    cout << isCyclic(v, adj) << endl;
  }
  return 0;
}
