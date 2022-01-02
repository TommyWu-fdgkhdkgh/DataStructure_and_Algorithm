#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

/*
  network  flow  -->
    residual flow graph R(G, f) ， 這個結構除了原本的圖以外，也有跟原圖的邊同向的 "capacity" ， 也有跟圖反向的 "flow"
      "residule" = "capacity - flow" 

    "augment path : "


 */

typedef struct EDGENODE{
  int v;
  int capacity;
  int flow;
  int residual;
  struct EDGENODE *next; 
} edgenode;

typedef struct GRAPH{
  vector<vector<edgenode>> edges;
} flow_graph;

flow_graph g;

edgenode *find_edge(flow_graph *g, int x, int y) {
  edgenode *p;

  p = g->edges[x];

  while(p != NULL) {
    if(p->v == y) return p;
    p = p->next;
  }

  return NULL;
}

int path_volume(flow_graph *g, int start, int end, int parents[]) {
  edgenode *e;
  
  if (parents[end] == -1) return 0;

  e = find_edge(g, parents[end], end);

  if (start == parents[end]) {
    return e->residual;
  } else {
    return min(path_volume(g, start, parents[end], parents), e->residual);
  }


}

void augment_path(flow_graph *g, int start, int end, int parents[], int volume) {
  edgenode *e;

  if(start == end) return;

  e = find_edge(g, parents[end], end);
  e->flow += volume;
  e->residual -= volume;

  e = find_edge(g, end, parents[end]);
  e->residual += volume;

  augment_path(g, start, parents[end], parents, volume);

}


bool valid_edge(edgenode *e) {
  if (e->residual > 0) return true;
  else return false;
}


void netflow(flow_graph *g, int source, int sink) {
  int volume;

  add_residual_edges(g);

  initialize_search(g);
  bfs(g, source);

  volume = path_volume(g, source, sink, parent);

  while(volume > 0) {
    augment_path(g, source, sink, parent, volume);
    initialize_search(g);
    bfs(g, source);
    volume = path_volume(g, source, sink, parent);
  }
}


int main() {

   


  return 0;
}


