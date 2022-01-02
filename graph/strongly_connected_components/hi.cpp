// { Driver Code Starts
#include<bits/stdc++.h>

using namespace std;

 // } Driver Code Ends


/*  Function to find the number of strongly connected components
*   using Kosaraju's algorithm
*   V: number of vertices
*   adj[]: array of vectors to represent graph
*/


vector<bool> discovered;
vector<bool> processed;
vector<int> st; 
int ans = 0;


void DFS(int start, vector<int> adj[]) {

  discovered[start] = true;

  for(int i = 0;i < adj[start].size();i++) {
    int nowy = adj[start][i];

    if(!discovered[nowy]) {
      DFS(nowy, adj);
    }
  }

  processed[start] = true;
  st.push_back(start);
}


int kosaraju(int V, vector<int> adj[])
{
  
  discovered = vector<bool>(V, false);
  processed = vector<bool>(V, false);
  ans = 0;

  for(int i = 0;i < V;i++) {
    if(!discovered[i]) {
      DFS(i, adj);
    }
  }

  vector<int> transpose_adj[V];  
  for(int i = 0;i < V;i++) {
    for(int j = 0;j < adj[i].size();j++) {
      //cout << "i : " << i << endl;
      //cout << "adj[i][j] : " << adj[i][j] << endl;
      transpose_adj[adj[i][j]].push_back(i);
    }
    discovered[i] = false;
    processed[i] = false;
  }

  for(int i = st.size()-1;i >= 0;i--) {
    cout << " " << st[i];
  }
  cout << endl;

  while(st.size() != 0) {
    int nowstart = st.back();
    cout << "nowstart : " << nowstart << endl;
    st.pop_back();
    if(!discovered[nowstart]) {
      DFS(nowstart, transpose_adj);
      ans++;
    }
  }
  // Your code here
  return ans; 
}

// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int m, n;
        vector<int> adj[a];
        for (int i = 0; i < b; i++) {
            cin >> m >> n;
            adj[m].push_back(n);
        }
        cout << kosaraju(a, adj) << endl;
    }
    return 0;
}
  // } Driver Code Ends
