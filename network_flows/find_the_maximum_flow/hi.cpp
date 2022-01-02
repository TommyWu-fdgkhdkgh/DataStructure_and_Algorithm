// 題目 : https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
//        https://practice.geeksforgeeks.org/problems/find-the-maximum-flow/0
  
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


typedef struct EDGENODE {
  int y;
  int capacity;
  int residual; 
  int flow;
} edgenode;

/*

Notice: TC uses random generator and several edges may link two vertices (just add them into one with sum of capacity) they are NON-DIRECTIONAL so "1 2 5 ... 2 1 8" is equivalent to "1 2 13". Also it sometimes will loop vertex. Ignore such edge.

發現這個東西的人是鬼吧.... 太強了

 */


// 因為是 undirected graph ，這樣子 residual 會是怎麼樣呢?
// me : 試試看，當有流從 A->B = x 時， 
//      A.residual -= x;
//      A.flow += x;
//      B.residual += x;
//      B.flow -= x;
void insert_edge(vector<vector<edgenode>> &rg, int x, int y, int z) {

  for(int i = 0;i < rg[x].size();i++) {
    if(rg[x][i].y == y) {
      rg[x][i].capacity += z;
      rg[x][i].residual += z;

      for(int j = 0;j < rg[y].size();j++) {
        if(rg[y][i].y == x) {
          rg[y][i].capacity += z;
	  rg[y][i].residual += z;

	  return;
	}
      }

      return;
    }
  }

  //////////////

  edgenode newe;
  newe.y = y;
  newe.capacity = z;
  newe.residual = z;
  newe.flow = 0;

  rg[x].push_back(newe); 

  newe.y = x;
  newe.capacity = z;
  newe.residual = z;
  newe.flow = 0;

  rg[y].push_back(newe);
}

void reset_parents(vector<int> &parents) {
  for(int i = 0;i < parents.size();i++) {
    parents[i] = -1;
  }
}

void bfs(vector<vector<edgenode>> &rg, vector<int> &parents, int source, int sink) {
  
  queue<int> q;
  vector<bool> visited = vector<bool>(parents.size(), false);

  q.push(source);
  visited[source] = true;
  
  while(!q.empty()) {
    int now = q.front();
    q.pop(); 

    visited[now] = true;
  
    //cout << "now : " << now << endl;

    // index 在這題是從 1 開始
    for(int i = 1;i < rg[now].size();i++) {
      edgenode e = rg[now][i];
      
      if(!visited[e.y] && e.residual > 0) {
        parents[e.y] = now;
        q.push(e.y);
      }
    }

  }
}

edgenode find_path(int x, int y, vector<vector<edgenode>> &rg) {
  edgenode e;
  e.y = -1;

  for(int i = 0;i < rg[x].size();i++) {
    if(rg[x][i].y == y) {
      e = rg[x][i];
    }
  }
  return e;
}

int path_volume(vector<int> &parents, vector<vector<edgenode>> &rg, int start, int end) {

  if(parents[end] == -1) {
    return 0;    
  } else if (start == parents[end]){
    return find_path(start, end, rg).residual;
  } else {
    return min(path_volume(parents, rg, start, parents[end]), find_path(parents[end], end, rg).residual);
  }

  return 0;
}

void augment_path(int volume, vector<vector<edgenode>> &rg, vector<int> &parents, int start, int end) {
 
  if(parents[end] == -1) {
    return;
  }	 
  
  int x = parents[end];
  int y = end;

  for(int i = 0;i < rg[x].size();i++) {
    if(rg[x][i].y == y) {
      rg[x][i].flow += volume;
      rg[x][i].residual -= volume;
      break;
    } 
  }
  for(int i = 0;i < rg[y].size();i++) {
    if(rg[y][i].y == x) {
      rg[y][i].flow -= volume;
      rg[y][i].residual += volume;
      break; 
    }
  }

  augment_path(volume, rg, parents, start, parents[end]);

}

int max_flow(vector<vector<edgenode>> &rg, int N) {

  int flow = 0;

  vector<int> parents = vector<int>(rg.size(), -1);
  bfs(rg, parents, 1, N);          // find an augmented path

  while(parents[N] != -1) {

    int volume = path_volume(parents, rg, 1, N);  // 
    augment_path(volume, rg, parents, 1, N);
    //cout << "volume : " << volume << endl;
    flow += volume;

    reset_parents(parents);
    bfs(rg, parents, 1, N);
  }

  /*for(int end = N;parents[end] != -1; end = parents[end]) {
    cout << "parents[end] : " << parents[end] << endl;
  }*/

  //cout << "flow : " << flow << endl;
  //cout << flow << endl;
  return flow;
}

int main() {

  vector<vector<edgenode>> rg;
  

  int T;
  cin >> T;
  while(T--) {
    int N, M;
    cin >> N >> M; 

    rg = vector<vector<edgenode>>(N + 1, vector<edgenode>(N + 1));

    for(int i = 0;i < M;i++) {
      int x, y, z;
      cin >> x >> y >> z;
      //cout << "x : " << x << ", y : " << y << ", z : " << z << endl;

      insert_edge(rg, x, y, z);

     } 
     int ans = max_flow(rg, N);
     cout << ans << endl;
  }

  return 0;
}

