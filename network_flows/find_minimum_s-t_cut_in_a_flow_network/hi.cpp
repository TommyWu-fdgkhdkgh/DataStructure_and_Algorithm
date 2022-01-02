// 題目 : https://www.geeksforgeeks.org/minimum-cut-in-a-directed-graph/
// 猜測 :  1. 作一次最大流，這次的邊記得要記上 original_residual
//         2. 做好後，再進行一次 BFS ， 碰到 original_residual > 0 但是 residual == 0 ， 這個邊應該就算是 minimum-s-t-cut 的一員了

// TODO參考了解答的取 minimum st cut 的方式 QQ

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;


// 這次試試 adjacency matrix


typedef struct EDGENODE{
  int original_residual;
  int residual;
  int capacity;
  int flow;
} edgenode;


//void bfs()
//path_volume()
//augment_pah()
//init_parents;
//void get_minimum_st_cut

void bfs(vector<vector<edgenode>> &adj, int source, int sink, vector<int> &parents) {
  vector<bool> visited = vector<bool>(adj.size(), false);

  queue<int> q;
  q.push(source);

  visited[source] = true;

  while(!q.empty()) {
    int now = q.front();
    q.pop();
  
    // we find the sink
    if(now == sink) {
      break;
    }

    for(int i = 0;i < adj[now].size();i++) {
      if(adj[now][i].residual > 0 && adj[now][i].capacity > 0 && !visited[i]) {
        visited[i] = true;
	parents[i] = now;
	q.push(i);
      }
    }
  
  }

}

// TODO
int path_volume(vector<vector<edgenode>> &adj, int start, int end, vector<int> &parents) {
  
  if(parents[end] == -1) {
    return 0;
  } else if(parents[end] == start) {
    return adj[start][end].residual;
  } else if(parents[end] != start) {
    return min(path_volume(adj, start, parents[end], parents), adj[parents[end]][end].residual);
  }

  return -1e9;
}

void augment_path(vector<vector<edgenode>> &adj, int start, int end, vector<int> &parents, int volume) {
  if(parents[end] == -1) {
    return; 
  } else if(parents[end] == start) {
    adj[start][end].residual -= volume;
    adj[start][end].flow += volume;
    adj[end][start].residual += volume;
  } else if (parents[end] != start) {
    adj[parents[end]][end].residual -= volume;
    adj[parents[end]][end].flow += volume;
    adj[end][parents[end]].residual += volume;

    augment_path(adj, start, parents[end], parents, volume);
  }
} 

void init_parents(vector<int> &parents) {
  for(int i = 0;i < parents.size();i++) {
    parents[i] = -1;
  }
}

int max_flow(vector<vector<edgenode>> &adj, int source, int sink) {


  vector<int> parents = vector<int>(adj.size(), -1);

  bfs(adj, source, sink, parents);

  int flows = 0;

  while(parents[sink] != -1) {
    int volume = path_volume(adj, source, sink, parents);
    augment_path(adj, source, sink, parents, volume);
    
    flows += volume;

    init_parents(parents);
    bfs(adj, source, sink, parents);
  }

  //cout << "flows : " << flows << endl;

  
  /*for(int i = 0;i < adj.size();i++) {
    for(int j = 0;j < adj[0].size();j++) {
      cout << " " << adj[i][j].original_residual;
    }
    cout << endl;
  }*/
  return 0;
}

void get_minimum_st_cut(vector<vector<edgenode>> &adj, vector<int> &ans, int source) {
  
  vector<bool> visited = vector<bool>(adj.size(), false);

  queue<int> q;
   
    q.push(source);
    visited[source] = true;
    while(!q.empty()) {
      int now = q.front();
      q.pop();

      for(int i = 0;i < adj[now].size();i++) {
        //method 1
        /*if(adj[now][i].original_residual > 0 && adj[now][i].residual == 0) {
          ans.push_back(now);
          ans.push_back(i);
        }*/

        if(adj[now][i].residual > 0 && adj[now][i].original_residual > 0 && !visited[i] && adj[now][i].capacity > 0) {  
          visited[i] = true;
   	  q.push(i);
        }
      }
    }

  // method 2
  for(int i = 0;i < adj.size();i++) {
    for(int j = 0;j < adj[0].size();j++) {
      if(adj[i][j].original_residual > 0 && visited[i] && !visited[j]) {
        ans.push_back(i);
	ans.push_back(j);
      }
    }
  }
  // method 1 會錯! 需要好好探究出錯的原因
  // method 2 是向解答抄ㄉQQ

}

int main () {

  vector<vector<edgenode>> adj;    

  int T;
  cin >> T;

  int numv;

  while(T--) {
    cin >> numv;

    adj = vector<vector<edgenode>>(numv, vector<edgenode>(numv));

    /*for(int i = 0;i < numv;i++) {
      for(int j = 0;j < numv;j++) {
        adj[i][j].original_residual = 0;
        adj[i][j].residual = 0;
        adj[i][j].capacity = 0;
        adj[i][j].flow = 0;
      }
    }*/

    for(int i = 0;i < numv;i++) {
      for(int j = 0;j < numv;j++) {
        int w;
	cin >> w;
	adj[i][j].original_residual = w;
	adj[i][j].residual = w;
	adj[i][j].capacity = w;
	adj[i][j].flow = 0;
      }
    }
    int source, sink;
    cin >> source >> sink;

    max_flow(adj, source, sink);

    vector<int> ans;

    get_minimum_st_cut(adj, ans, source);

    int i = 0;
    if(ans.size() != 0) {
      for(i = 0;i < ans.size()-1 ;i++) {
        cout << ans[i] << " ";
      }
      cout << ans[i] << endl;
    } else {
      cout << "-1" << endl;
    }
  } 

  return 0;
}

