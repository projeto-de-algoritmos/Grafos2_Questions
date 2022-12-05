// ----------------------------------------- Bibliotecas & Macros --------------------------------------- //

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ------------------------------------------ Funções da Queue ------------------------------------------ //

    // queue - estrutura da fila
    typedef struct queue {
        int key;
        struct queue *next;
    } queue;

    queue* fila = NULL;
    
    // Push - Adiciona um elemento na fila (FIFO - First In First Out)
    void push(int x) {
        queue *aux = malloc(sizeof(queue));
        aux->key = x;
        aux->next = NULL;
        if (fila == NULL)
            fila = aux;
        else {
            queue *aux2 = fila;
            while (aux2->next != NULL) // Encontra o ultimo elemento da fila
                aux2 = aux2->next;
            aux2->next = aux;
        }
    }
    // Get - Retorna o primeiro elemento da fila
    int get() {
        int x = fila->key;
        queue *aux = fila;
        fila = fila->next;
        free(aux);
        return x;
    }
    // isEmpty - Verifica se a fila está vazia
    int isEmpty() {
        if (fila == NULL) return 1;
        return 0;
    }

// -------------------------------- Funções auxiliares & Variáveis Globais -------------------------------- //

// Variaveis Globais
int n, m, c, k, grafo[1000][1000], custo[1000];

// Função auxiliar que inicializa o grafo e o vetor de custo
void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grafo[i][j] = INT_MAX;
        }
        custo[i] = INT_MAX;
    }
}

// ----------------------------------------------- Dijkstra ---------------------------------------------- //

// Dijkstra
int dijkstra(int ori, int dest){
	custo[ori] = 0;
	push(ori);
	while(!isEmpty()){
		int i = get();
		for(int j=0; j<n; j++){
            /*
                - Se existe uma aresta entre i e j (grafo[i][j] != INT_MAX)
                - Se o custo de j é maior que o custo de i + o custo da aresta (custo[j] > custo[i] + grafo[i][j])
            */
			if(grafo[i][j] != INT_MAX && custo[j] > custo[i] + grafo[i][j]){
				custo[j] = custo[i] + grafo[i][j]; // Atualiza o custo de j --> garante o menor caminho
				push(j);
			}
		}
	}
	return custo[dest];
}

// -------------------------------------------------- Main -------------------------------------------------- //

int main() {
    /*
    Leitura dos dados
    n = numero de cidades
    m = numero de estradas
    c = numero de cidades na rota de serviço
    k = cidade onde o veiculo foi concertado
    */
    
    while(scanf("%d %d %d %d", &n, &m, &c, &k) == 4){
        if (n == 0 && m == 0 && c == 0 && k == 0) break;
        // Inicializa o grafo e o vetor de custo
        init();
        // Leitura do grafo - Estradas
        for(int i = 1; i <= m; i++){
            /*
            Leitura das arestas
            u = cidade de origem
            v = cidade de destino
            p = custo da estrada
            */
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);
            // se as duas cidades estiverem fora da rotas
            if(u>=c && v>=c){
                // adicione a arestra normalmente (ida e volta)
                grafo[u][v]=p;
                grafo[v][u]=p;
            }
            // se v pertencer à rota
            if(u>=c && v<c) grafo[u][v]=p; // adicione apenas a estrada que chega em v
            
            // se u pertencer à rota
            if(u<c && v>=c) grafo[v][u]=p; // adicione apenas a estrada que chega em u
            
            // se as duas cidades forem cidades consecutivas da rota
            if(u<c && v<c && abs(u-v)==1){ // u<c && v<c significa que u e v pertencem à rota
                //adiciono a estrada normalmente
                grafo[u][v]=p;
                grafo[v][u]=p;
            }
        }
    // imprimindo o valor do menor caminho a partir do algoritmo de Dijkstra
    printf("%d\n", dijkstra(k, c-1));
    }
    return 0;
}