#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX
#include <stdbool.h> // bool, true, false

// pair - estrutura que armazena um par de inteiros
typedef struct {
  int first;
  int second;
} pair;

// vector - estrutura que armazena um vetor de pares de inteiros
typedef struct {
  int size;
  pair *data; // vetor de pares de inteiros
} vector;

// graph - estrutura que armazena um grafo
typedef struct {
  int size;
  vector *data; // vetor de vetores de pares de inteiros
} graph;

// max - retorna o maior valor entre dois inteiros
int max (int a, int b){
  if (a == INT_MAX)
    return b;
  if (b == INT_MAX)
    return a;
  return a > b ? a : b;
}

// min - retorna o menor valor entre dois inteiros
int min (int a, int b){
  if (a == INT_MAX)
    return b;
  if (b == INT_MAX)
    return a;
  return a < b ? a : b;
}

// dijkstra - algoritmo de dijkstra para encontrar o menor caminho entre dois vertices
int dijkstra (graph *g, int n, int x, int y){

  int *dist = (int*) malloc (n * sizeof(int));
  int *h = (int*) malloc (n * sizeof(int));
  
  for (int i=0; i<n; i++){
    dist[i] = INT_MAX;
    h[i] = INT_MAX;
  }
  
  dist[x] = 0;
  h[x] = INT_MAX;
    
  if (x == y)
    return 0;
  
  while (true){
    int u = -1;
    int minimo = INT_MAX;
    for (int i=0; i<n; i++){
      if (dist[i] < minimo){
        minimo = dist[i];
        u = i;
      }
    }
    
    if (u == -1) break;
    
    dist[u] = INT_MAX;
    
    for (int i=0; i<g->data[u].size; i++){
      int v = g->data[u].data[i].second;
      int cost = g->data[u].data[i].first;
      if (h[v] > max(h[u], cost)){
        h[v] = min(h[v], max(h[u], cost));
        dist[v] = h[v];
      }
    }
  }
  
  return h[y]; 
}

int main (){
  
  int t = 1;
  
  while (true){
    /*
      n - numero de interseções
      m - numero de ruas
    */
    int n, m;
    scanf("%d %d", &n, &m);
    if (n == 0 && m == 0) break;
  
    // GraphInit - inicializa o grafo
    graph *g = (graph*) malloc (sizeof(graph));
    g->size = n;
    g->data = (vector*) malloc (n * sizeof(vector));
    for (int i=0; i<n; i++){
      g->data[i].size = 0;
      g->data[i].data = NULL;
    }
    
    // Monta o grafo
    for (int i=0; i<m; i++){
      /*
        a = i = vertice de origem
        b = j = vertice de destino
        c = h = custo da aresta (peso)
      */
      int a, b, c;
      scanf("%d %d %d", &a, &b, &c);
      a--; b--; // os vetores começam em 0
      
      g->data[a].size++; // aumenta o tamanho do vetor de pares
      g->data[a].data = (pair*) realloc (g->data[a].data, g->data[a].size * sizeof(pair)); // realoca o vetor de pares
      // adiciona o par (c, b) no vetor de pares
      g->data[a].data[g->data[a].size-1].first = c;
      g->data[a].data[g->data[a].size-1].second = b; 
      
      // Como o grafo é bidirecional, é necessário adicionar o par (c, a) no vetor de pares de b

      g->data[b].size++; // aumenta o tamanho do vetor de pares
      g->data[b].data = (pair*) realloc (g->data[b].data, g->data[b].size * sizeof(pair)); // realoca o vetor de pares
      // adiciona o par (c, a) no vetor de pares 
      g->data[b].data[g->data[b].size-1].first = c;
      g->data[b].data[g->data[b].size-1].second = a;
    }

    printf("Instancia %d\n", t++);
    int k;
    scanf("%d", &k);
    for (int i=0; i<k; i++){
      int u, v;
      scanf("%d %d", &u, &v);
      printf("%d\n", dijkstra(g, n, u-1, v-1)); // para cada par de vertices, chama o algoritmo de dijkstra para encontrar o menor caminho
    }
    printf("\n");  }
  return 0;
}
