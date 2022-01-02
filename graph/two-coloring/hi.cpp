#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

enum COLOR{
  YEL,
  RED,
  BLUE
};


int BFS(int start, vector<vector<int>> &g, vector<int> &color, vector<vector<bool>> &visited) {
  queue<int> q;
  q.push(start);
  if(color[start] == YEL) {
    color[start] = RED;
  }

  while(!q.empty()) {
    int now = q.front();
    int nowcolor = color[now];

    q.pop();
      
    for(int i = 0;i < g.size();i++) {
      if(g[now][i] == 1 && visited[now][i] == false) {
        visited[now][i] = true;
	
	if(color[i] == YEL) {
          if(nowcolor == RED) {
            color[i] = BLUE;
	  } else {
            color[i] = RED;
	  }
	  q.push(i);
	} else if (color[i] == nowcolor) {
          return 0;
	} else {
          q.push(i);
	}
      } 
    }   
  }

  return 1;

}

int main() {
  
  int T;
  int numV;
  vector<vector<int>> g;
  vector<vector<bool>> visited;
  vector<int> color; 

  cin >> T;

  while(T--) {
    cin >> numV;
   
    g = vector<vector<int>>(numV, vector<int>(numV, 0));
    visited = vector<vector<bool>>(numV, vector<bool>(numV, 0)); //記錄這個 edge 有沒有走過。
    color = vector<int>(numV, YEL);
   
    int result = 1;

    for(int i = 0;i < g.size();i++) {
      for(int j = 0;j < g.size();j++) {
        cin >> g[i][j]; 
	if(i == j && g[i][j]) { // 檢查連向自己的邊，因為連向自己，一定不會是 bipartite graph (好妙的測資...)
          result = 0; 
	}	
	//cout << " " << g[i][j];
      }
      //cout << endl;
    }
   
    if(result == 0 ) {
      cout << "0" << endl;
      continue;
    } 

    for(int i = 0;i < g.size();i++) {
      // 還沒走過
      result = BFS(0, g, color, visited);

      if(result == 0) {
        //cout << 0 << endl;
        break;
      }
    }

    if(result == 1) {
      cout << "1" << endl;
    } else {
      cout << "0" << endl;
    }
    g.clear(); 
    color.clear();
    visited.clear();
  }

  return 0;
}
