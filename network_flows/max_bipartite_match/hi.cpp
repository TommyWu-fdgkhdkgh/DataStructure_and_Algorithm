// 初始化好圖了 ， 但還缺把 source 跟 sink 接上原圖


#include <bits/stdc++.h>
using namespace std;

#define M 100
#define N 100

/*
  Q: job 會有 edge 指向 applicants 嗎?

 */


int maxBPM(bool bpGraph[M][N],int m,int n);
int main()
{
	int t;
	cin>>t;
	while(t--){
		int m,n;
		cin>>m>>n;		
		bool bpGraph[M][N];
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				cin>>bpGraph[i][j];
		cout << maxBPM(bpGraph,m,n)<<endl;
	}
    return 0;
}// } Driver Code Ends


typedef struct EDGENODE {
  int y;
  int residual;
  int flow;
  int capacity;
} edgenode;

void insert_edge(vector<vector<edgenode>> &adj, int x, int y) {
  edgenode e;
  e.y = y;
  e.residual = 1;
  e.capacity = 1;
  e.flow = 0;
  
  adj[x].push_back(e);

  e.y = x;
  e.residual = 0;
  e.capacity = 0;
  e.flow = 0;

  adj[y].push_back(e);

}

void bfs(vector<vector<edgenode>> &adj, int source, int sink, vector<int> &parents) {
  vector<bool> visited = vector<bool>(parents.size(), false);

  queue<int> q;
  q.push(source);
  
  visited[source] = true;

  while(!q.empty()) {
    int now = q.front();
    q.pop();

    if(now == sink) {
      break;
    } 

    for(int i = 0;i < adj[now].size();i++) {
      if(!visited[adj[now][i].y] && adj[now][i].residual > 0 && adj[now][i].capacity > 0) {

        visited[adj[now][i].y] = true;
        parents[adj[now][i].y] = now; 
        q.push(adj[now][i].y);

      }
    }
  }


}

int path_volume(vector<vector<edgenode>> &adj, int start, int end, vector<int> &parents) {

  if(parents[end] == -1) {
    return 0;
  } else if(parents[end] == start) {
    edgenode e;
    for(int i = 0;i < adj[start].size();i++) {
      if(adj[start][i].y == end) {
        e = adj[start][i];
	break;
      }
    }
    return e.residual;
  } else if(parents[end] != start) {

    edgenode e;
    for(int i = 0;i < adj[parents[end]].size();i++) {
      if(adj[parents[end]][i].y == end) {
        e = adj[parents[end]][i];
	break;
      }
    }

    return min(path_volume(adj, start, parents[end], parents), e.residual);
  }
}

void augment_path(vector<vector<edgenode>> &adj, int start, int end, vector<int> &parents, int volume) {
  
  cout << end << endl;

  if(parents[end] == -1) {
    return;
  } else if(parents[end] == start) {
    for(int i = 0;i < adj[start].size();i++) {
      if(adj[start][i].y == end) {
        adj[start][i].residual -= volume;
	adj[start][i].flow += volume;
	break;
      }
    }

    for(int i = 0;i < adj[parents[end]].size();i++) {
      if(adj[parents[end]][i].y == start) {
        adj[parents[end]][i].residual += volume;
	break;
      }
    }
    
  } else if(parents[end] != start) {
    for(int i = 0;i < adj[parents[end]].size();i++) {
      if(adj[parents[end]][i].y == end) {
        adj[parents[end]][i].residual -= volume;
	adj[parents[end]][i].flow += volume;
	break;
      }
    }

    for(int i = 0;i < adj[end].size();i++) {
      if(adj[end][i].y == parents[end]) {
        adj[end][i].residual += volume;
	break;
      }
    }

    augment_path(adj, start, parents[end], parents, volume);
  }

}

void init_parents(vector<int> &parents) {
  for(int i = 0;i < parents.size();i++) {
    parents[i] = -1;
  } 
}

int max_flow(vector<vector<edgenode>> &adj, int source, int sink) {

/*
  1. source 以 residual >= 1 為限，走到 sink
  2. 沿路蒐集可流過的最大流
  3. 沿路減掉流量

 */
  vector<int> parents = vector<int>(sink + 1, -1);
  bfs(adj, source, sink, parents);

  /*int now = sink;
  cout << sink << endl;
  for(;parents[now] != -1;now = parents[now]) {
    cout << now << endl;
  }*/
  int ans = 0;

  while(parents[sink] != -1) {

    cout << "---------" << endl; 
    int volume = path_volume(adj, source, sink, parents);
    cout << "---------" << endl; 
    //cout << "volume : " << volume << endl;

    ans += volume;
    //  
    augment_path(adj, source, sink, parents, volume);
    
    init_parents(parents);
    bfs(adj, source, sink, parents); 
  }

  return ans;
}

/*Complete the function below*/
int maxBPM(bool bpGraph[M][N],int m,int n)
{
//add code here.

  unordered_map<int, int> m2index;
  unordered_map<int, int> n2index; 
  vector<vector<edgenode>> adj = vector<vector<edgenode>>(m+n+2);

  int source = 0;
  int sink;

  int index = 1;
  for(int i = 0;i < m;i++) {
    m2index[i] = index;
    index++; 
  }
  for(int i = 0;i < n;i++) {
    n2index[i] = index;
    index++;
  }
  sink = index;

  for(int i = 0;i < m;i++) {
    for(int j = 0;j < n;j++) {
      if(bpGraph[i][j]) {
        //cout << "a new edge !" << endl;
        insert_edge(adj, m2index[i], n2index[j]);
      }
    } 
  }


  for(int i = 0;i < m;i++) {
    insert_edge(adj, source, m2index[i]); 
  }

  for(int i = 0;i < n;i++) {
    insert_edge(adj, n2index[i], sink);
  }

  return max_flow(adj, source, sink);
}





