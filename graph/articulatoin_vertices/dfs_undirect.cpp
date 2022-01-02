// reference : the algorithm design manual 2nd
// adjacency list
//   basic operation, bfs, dfs

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

#define MAXV 1000
//#define UNDISCOVERED 0
//#define DISCOVERED 1
//#define PROCESSED 2

using namespace std;

typedef struct edgenode{
  int y;
  int weight;
  struct edgenode *next;
} edgenode;

typedef struct graph{
  edgenode *edges[MAXV+1];
  int degree[MAXV+1];
  int nvertices;
  int nedges;
  bool directed;
} graph;

void initialize_graph(graph *g, bool directed) {
  int i;
  
  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;
  
  for (i = 1;i <= MAXV;i++) {
    g->degree[i] = 0;
    g->edges[i]  = NULL;
  }
}

void insert_edge(graph *g, int x, int y, bool directed) {
  edgenode *p;
  
  p = (edgenode *)malloc(sizeof(edgenode));
  p->weight = 0;
  p->y = y;
  p->next = g->edges[x];

  g->edges[x] = p;
  g->degree[x]++;

  if(directed) {
    g->nedges++;
  } else {
    insert_edge(g, y, x, true);
  }
}

void read_graph(graph *g, bool directed) {
  int i;
  int m;
  int x, y;

  initialize_graph(g, directed);
  
  scanf("%d %d", &(g->nvertices), &m);
  
  for(i = 1;i <= m;i++){
    scanf("%d %d", &x, &y);
    insert_edge(g, x, y, directed);
  }

}

void print_graph(graph *g) {
  int i;
  edgenode *p;

  for(i = 0;i < g->nvertices;i++) {
    printf("%d : ", i);
    p = g->edges[i];
    while(p != NULL) {
      printf(" %d", p->y);
      p = p->next;
    }
    printf("\n");
  }
}

enum TEST {
  FALSE,
  TRUE
};

enum TREE_TYPE {
  TREE, 
  BACK
};

bool processed[MAXV + 1];
bool discovered[MAXV + 1];
int entry_time[MAXV + 1];
int exit_time[MAXV + 1];
int parent[MAXV + 1];
int now_time;
int finished = FALSE;
int reachable_ancestor[MAXV + 1];
int tree_out_degree[MAXV + 1];
//me :  這裡的 tree_out_degree 並不是原圖上的 out_degree ， 而是 dfs tree 上的 out degree

void initialize_search(graph *g) {
  int i;

  for(i = 0;i <= g->nvertices;i++) {
    processed[i] = discovered[i] = FALSE;
    parent[i] = -1;
    entry_time[i] = -1;
    exit_time[i] = -1;
    tree_out_degree[i] = 0;
  }

  now_time = 0;

}


void find_path(int start, int end, int parents[]) {
  if((start == end) || (end == -1)) {
    if(end == -1) {
      printf("\ncannot find start value\n");
    } else {
      printf("\n%d", start);
    }
  } else {
    find_path(start, parents[end], parents);
    printf(" %d", end);
  }
}

int edge_classification(int x, int y) {
  if(parent[y] == x) {
    return TREE;
  } else if(discovered[y] && !processed[y]) {
    return BACK;
  }
}


void process_vertex_late(int v) {
  printf("[process late] processed vertex %d\n", v);

  bool root;
  int time_v;
  int time_parent;

  if (parent[v] < 0) {
    printf("hihi\n");
    printf("tree_out_degree[v]: %d\n", tree_out_degree[v]);
    if (tree_out_degree[v] > 1) {
      printf("root articulation vertex\n");
    }
    return;
  }


  root = (parent[parent[v]] < 0);
  if((reachable_ancestor[v] == parent[v]) && (!root)) {
    printf("parent articulation vertex : %d \n", parent[v]);
  }

  if(reachable_ancestor[v] == v) {
    printf("bridge articulation vertex : %d\n", parent[v]);

    if(tree_out_degree[v] > 0) {
      printf("bridge articulation vertex : %d\n", v);
    }
  }


  // 我自己應該想不到這一步，也就是說，子節點可以到的最老節點，代表這個節點的 parent 也同樣到的了。
  //   這樣做更強力的效果是，這個值能夠慢慢往 parent 傳遞。
  time_v = entry_time[reachable_ancestor[v]];
  time_parent = entry_time[reachable_ancestor[parent[v]]];

  if(time_v < time_parent) {
    reachable_ancestor[parent[v]] = reachable_ancestor[v];
  }

}

void process_vertex_early(int v) {
  printf("[process early] processed vertex %d\n", v);

  reachable_ancestor[v] = v;
}

void process_edge(int x, int y) {
  int edge_type = edge_classification(x, y);

  if(parent[x] == y) {
    return;
  } else if(edge_type == TREE) {
    tree_out_degree[x] += 1;
    printf("tree out degree[%d]++\n", x);
  } else if(edge_type == BACK && parent[x] != y /* 我一定想不到這一步，就是父母節點並不算在 reachable_ancestor 裡。這也算是蠻重要的一步 */) {
    if(entry_time[y] < entry_time[reachable_ancestor[x]]) {
      reachable_ancestor[x] = y;
      processed[y] = TRUE;
    }
  }
}


void dfs(graph *g, int v) {
  edgenode *p;
  int y;

  if (finished) return;

  discovered[v] = TRUE;
  now_time = now_time + 1;
  entry_time[v] = now_time; 

  process_vertex_early(v);

  p = g->edges[v];
  while( p != NULL) {
    y = p->y;

    printf("now x : %d, y : %d\n", v, y);

    if(discovered[y] == FALSE) {
      printf("discover : y : %d\n", y);
      parent[y] = v;
      process_edge(v, y);
      discovered[y] = TRUE;
      dfs(g, y);  
    } else if((!processed[y]) || (g->directed)) {
      process_edge(v, y);
    } else if(parent[v] == y){
      //continue;  
    } else if(processed[y]){
      //assert(0);
    } else {
      assert(0);
    }

    if (finished) return;
    p = p->next;
  }

  process_vertex_late(v);

  now_time = now_time + 1;
  exit_time[v] = now_time;
  
  processed[v] = TRUE;

}


int main() {
  
  graph* g = (graph *)malloc(sizeof(graph));
  read_graph(g, false);   
  print_graph(g);


  printf("start to DFS\n");
  initialize_search(g);

  dfs(g, 0);

  //find_path(-1, 2, parent); 

  return 0;
}




