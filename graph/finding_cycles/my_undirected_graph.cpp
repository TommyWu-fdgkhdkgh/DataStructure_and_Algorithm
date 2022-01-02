#include <bits/stdc++.h>

using namespace std;



/*void BFS(vector<int> &g[], vector<bool> &visited, int index) {

}*/

bool isCyclic(vector<int> g[], int V) {
  

  vector<bool> visited = vector<bool>(V, false);
  vector<int> parents = vector<int>(V, -1);
  queue<int> q;

  for(int i = 0;i < V;i++) {
    if(visited[i] == false) {
      q.push(i);
      visited[i] = true;
      while(!q.empty()) {
        int now = q.front();
        q.pop();	
        
        for(int j = 0;j < g[now].size();j++) {
          // **要把父母節點過濾掉**
          if(visited[g[now][j]] && parents[now] != g[now][j]) {
            return true;
	  } else if(visited[g[now][j]]) {
            //break;
	    continue;
	  }

	  visited[g[now][j]] = true;
	  parents[g[now][j]] = now;
	  q.push(g[now][j]);
	}	
        	
      }
    }
  }
  return false;
}

int main () {
  int T;
  cin >> T;
  while(T--) {
    int V, E;
    cin >> V >> E; 
   
    // array of vectors to represent graph 
    vector<int> adj[V];   
   
    int u, v; 
    for(int i = 0;i < E;i++) {
      cin >> u >> v; 

      // adding edge to the graph
      // adj[i] = v  表示點 i 有邊連向點 v  
      adj[u].push_back(v);
      adj[v].push_back(u);

    }
    cout << isCyclic(adj, V) << endl;
  }
  return 0;
}





