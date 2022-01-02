// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
int spanningTree(int V, int E, vector<vector<int>> &graph);
// Driver code

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int> > graph(V, vector<int>(V, INT_MAX));
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            graph[u][v] = w;
            graph[v][u] = w;
        }

        cout << spanningTree(V, E, graph) << endl;
    }
    return 0;
}
// } Driver Code Ends


// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation, with V vertices.
// graph[i][j] = weight if edge exits else INT_MAX

vector<int> uparent;
vector<int> udegree;

int find(int x) {
  if(uparent[x] == x) {
    return x;
  } else {
    return uparent[x] = find(uparent[x]);
  }
}

void unite(int x, int y) {
  x = uparent[x];
  y = uparent[y];

  if(x == y) return;

  if(udegree[x] > udegree[y]) {
    uparent[y] = x;
  } else if(udegree[x] < udegree[y]){
    uparent[x] = y;
  } else {
    uparent[y] = x;
    udegree[x] += 1;
  }
}

typedef struct EDGE {

  int x;
  int y;
  int w;

}edge;

bool compare(edge a, edge b) {
  return a.w < b.w;
}

int spanningTree(int V, int E, vector<vector<int>> &graph) {
  // code here
  uparent = vector<int>(V+1, -1);
  udegree = vector<int>(V+1, 1);

  for(int i = 0;i <= V;i++) {
    uparent[i] = i;
  }

  // prim 感覺需要 prioriy queue 了
  // pair<w, y>
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  int ans = 0;
  
  for(int i = 1;i < graph[0].size();i++) {
    if(graph[0][i] == INT_MAX) {
      continue;
    }

    pair<int, int> newp;
    newp.first = graph[0][i];
    newp.second = i;
    pq.push(newp);
  }

  cout << "----" << endl;
  while(!pq.empty()) {
    pair<int, int> nowp = pq.top();
    pq.pop();
    int w = nowp.first;
    int y = nowp.second;

    //cout << "y :" << y << endl;
    //cout << "w :" << w << endl << endl;

    if(find(0) == find(y)) {
      continue;
    } else {
      ans += w;
      unite(0, y);
      
      for(int i = 0;i < graph[y].size();i++) {
        if(graph[y][i] == INT_MAX) {
          continue;
	}

        pair<int, int> newp;
	newp.first = graph[y][i];
	newp.second = i;
        pq.push(newp);
      }
    }
  }  
  //cout << "----" << endl;

  return ans;
}











