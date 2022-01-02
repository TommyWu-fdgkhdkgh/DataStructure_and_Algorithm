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

  vector<edge> sorted;

  for(int i = 0;i < graph.size();i++) {
    for(int j = i+1;j < graph.size();j++) {
      if(graph[i][j] != INT_MAX) {
        edge newe;
	newe.x = i;
	newe.y = j;
	newe.w = graph[i][j];
        sorted.push_back(newe);
      }
    }
  }

  sort(sorted.begin(), sorted.end(), compare);

  /*
  cout << "--------" << endl;
  for(int i = 0;i < sorted.size();i++) {
    cout << "sorted[i].w : " << sorted[i].w << endl;  
  }
  cout << "--------" << endl;
  */

  int ans = 0;
  for(int i = 0;i < sorted.size();i++) {
    if(find(sorted[i].x) != find(sorted[i].y)) {
      ans += sorted[i].w;
      unite(sorted[i].x, sorted[i].y);
    }
  }


  return ans;
}











