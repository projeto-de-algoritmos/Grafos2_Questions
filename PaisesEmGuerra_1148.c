// ------------------------------------- Bibliotecas & Macros & Globais ---------------------------------- //

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define city(n) ((n) - 1)

// Variaveis globais
int n; // numero de cidades (max = 500)
int e; // numero de estradas
int k; // numero de cidades que devem ser visitadas
int grafo[500][500]; // matriz de adjacencia

// -------------------------------- Funções auxiliares & Variáveis Globais -------------------------------- //

// Função auxiliar que inicializa o grafo com infinito
void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grafo[i][j] = INT_MAX;
        }
    }
}

// ----------------------------------------------- Dijkstra ---------------------------------------------- //

// Dijkstra adaptado para encontrar o menor caminho entre dois vertices
int dijkstra(int ori, int dest){
    
    /*
    dist - vetor de distancias entre o vertice de origem e os demais vertices do grafo
    visitado - vetor de visitados (1 = visitado, 0 = nao visitado)
    u - vertice atual
    */
    int dist[n], visitado[n], min, u;
    
    // Inicializa distancias e visitados
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
    }

    // Inicializa distancia da origem  
    dist[ori] = 0;

    // Enquanto existir vertices nao visitados
    for (int i = 0; i < n; i++) {
        min = INT_MAX;

        // Encontra vertice nao visitado com menor distancia
        for (int j = 0; j < n; j++) {
            // Se a distancia for menor que a minima e o vertice nao foi visitado
            if (visitado[j] == 0 && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        // Marca vertice como visitado
        visitado[u] = 1;

        // Atualiza distancias dos vizinhos
        for (int j = 0; j < n; j++) {
            /*
               - Se o vertice nao foi visitado (visitado[j] == 0)
               - E se existe uma ligacao entre o vertice atual e o vertice j (grafo[u][j] != INT_MAX)
                - E se a distancia do vertice atual + a distancia do vertice atual para o vertice j for menor que a distancia do vertice j
            */
            if (visitado[j] == 0 && grafo[u][j] != INT_MAX && dist[u] + grafo[u][j] < dist[j]) {
                dist[j] = dist[u] + grafo[u][j];
            }
        }
    }

    // Retorna distancia do destino
    return dist[dest];
}

// ------------------------------------------------ Main ------------------------------------------------- //

int main(){
   while (scanf("%d %d", &n, &e) == 2){
        if (n == 0 && e == 0) break;
        init();
        for (int i = 0; i < e; i++) {
            /*
            x = cidade de origem
            y = cidade de destino
            z = tempo de envio de mensagem
            */
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            // Se existe uma ligação entre x e y, então há uma ligação entre y e x
            if (grafo[city(y)][city(x)] < INT_MAX) {
                grafo[city(x)][city(y)] = 0;
                grafo[city(y)][city(x)] = 0;
            }
            else {
                grafo[city(x)][city(y)] = h;
            }
        }
        scanf("%d", &k);
        int horasTotais;
        for (int i = 0; i < k; i++) {
            /*
            o = cidade de origem
            d = cidade de destino
            */
            int o, d;
            scanf("%d %d", &o, &d);
            horasTotais = dijkstra(city(o), city(d));
            if (horasTotais == 0)
                printf("0\n");
            else if (horasTotais == INT_MAX)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", horasTotais);
        }
        printf("\n");
    }
    return 0;
}