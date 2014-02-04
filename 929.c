/*
* ====================================================================================================
*
*                               NUMBER MAZE
* 
* Nome do Arquivo: 10004.c
*
* Descrição: Consideramos um labirinto de números representado por uma matriz bidimensional com os va- 
*            lores entre 0 e 9. O labirinto pode ser percorrido em ortogonal (isto é, norte, sul, leste
*             e oeste). Considerando que cada célula representa um custo, em seguida, encontrar o custo 
*             mínimo para viajar pelo labirinto de um ponto de entrada para um ponto de saída.
*
* Data: 05/02/2014
*
* Autores: Silvana Trindade, Maurício A. Cinelli e Marivone Valentin
* 
* =====================================================================================================
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
 
#define MAX 1000
#define PQ_SIZE 3000


/*--------------------------------- PQ --------------------------------------*/

int min;
int x_min;
int y_min;

 /**
 * Utilizado em Dijkstra
 */
int distance[MAX][MAX];
int cost[MAX][MAX];
int visited[MAX][MAX];

/**
 * x =
 * y =
 * cost = custo do registro
 */
typedef struct {

    int x;
    int y;
    int cost;

} record;

/**
 * q = os elementos da lista
 * n = número de elementos da lista
 */
typedef struct {

    record q[PQ_SIZE + 1];
    int n; 

} priority_queue;

/**
 * Inicializa fila de prioridades
 * @param pq fila
 */
void pq_init(priority_queue *pq);

/**
 * Retorna o filho a esquerda
 * @param  parent_index indice do pai
 * @return              filho a esquerda
 */
int left_child(int parent_index);

/**
 * Retorna o filho a direita
 * @param  parent_index indice do nó pai
 * @return              filho a direita
 */
int right_child(int parent_index);

/**
 * Retorna o nó pai de um filho
 * @param  child_index indice do filho
 * @return indice fo nó pai
 */
int pq_parent(int child_index);

/**
 * [bubble_up description]
 * @param p           [description]
 * @param child_index [description]
 */
void bubble_up(priority_queue *p, int child_index); 

/**
 * [bubble_down description]
 * @param p            [description]
 * @param parent_index [description]
 */
void bubble_down(priority_queue *p, int parent_index);

/**
 * Remove o menor elemento da fila de prioridades
 * @param p Lista de prioridade
 */
void extract_min(priority_queue *p);

/**
 * Insere na fila de prioridades
 * @param p [ponteiro da fila de prioridade]
 * @param i [custo]
 * @param x [coordenada]
 * @param y [coordenada]
 */
void pq_insert(priority_queue *p, int i, int x, int y);

/**
 * Executa algoritmo de dijkstra
 * @param N numero de linhas
 * @param M numero de colunas
 * @param q fila de prioridade
 */
void dijkstra(int N, int M, priority_queue *q);

int main(void) {
    
    int test_cases, i, j, N, M;

    priority_queue *q = (priority_queue*) malloc (sizeof(priority_queue));
    
    if (q == NULL)
    {
        exit(1);
    }
    scanf("%d", &test_cases);
    
    /**
     * Enquanto existir caso de teste faça:
     * 
    */
    while (test_cases--) {
        
        /**
         * Lê número de linhas e colunas
         */
        scanf("%d\n%d", &N, &M);
        
        /**
         *  1 <= N, M <= 999
         */
        if (N > 1 && M > 999 )
        {
            exit(1);
        }
        /**
         * Preenche matriz com o custo 
         * set em matriz distance e visited
         */
        for (i = 0; i < N; i++) {

            for (j = 0; j < M; j++) {

                scanf("%d", &cost[i][j]);

                distance[i][j] = INT_MAX;
                visited[i][j] = 0;
            }
        }

        /**
         * Inicializa a fila de prioridades em cada caso de teste
         */
        pq_init(q);
        
        /**
         * Para cada labirinto, a saída de uma linha com o valor mínimo exigido.
         * Então utilizamos o algoritmo de Dijkstra para calcular o custo minimo
         */
        dijkstra(N, M, q);
        
        printf("%d\n", distance[N-1][M-1]);
    }
    return 0;
}

void pq_init(priority_queue *pq) {

    pq->n = 0;
}


/**
 * Calculos de filho e pai usando esquema de 
 * heap onde a arvore basicamente é um vetor
 */

int left_child(int parent_index) {
    return (2 * parent_index);
}

int right_child(int parent_index) {
    return (2 * parent_index) + 1;
}

int pq_parent(int child_index) {
    
    /**
     * root
     */
    if (child_index == 1)
    {
        return -1;
    }
    
    return ((int) child_index/2); /* chão esta implicito (trunca) */
}

/**
 * Faz com que um nó suba (se necessário) na árvore, através
 * de swaps, com isso é possível inserir um nó no final
 * e fazer ele 'borbulhar para cima'
 */
void bubble_up(priority_queue *p, int child_index) {
    
    int parent_index = pq_parent(child_index);
    int temp;
    
    /**
     * for for nó raiz, não faz nada
     */
    if (parent_index == -1)
    { 
        return;
    }
    
    /**
     * Porém, se o custo do filho sendo verificado for menor
     * do que o custo do nó pai, então faz um swap
     */
    if (p->q[parent_index].cost > p->q[child_index].cost) 
    { 
        /*Swap*/
        temp = p->q[child_index].cost;
        p->q[child_index].cost = p->q[parent_index].cost;
        p->q[parent_index].cost = temp;
        
        temp = p->q[child_index].x;
        p->q[child_index].x = p->q[parent_index].x;
        p->q[parent_index].x = temp;
        
        temp = p->q[child_index].y;
        p->q[child_index].y = p->q[parent_index].y;
        p->q[parent_index].y = temp;
        
        /**
         * Chama recursivamente, pois pode ser necessário múltiplas
         * trocas para que o nó chegue na posição correta da fila de
         * prioridades (arvore)
         */
        bubble_up(p, parent_index);
    }
    
}

/**
 * Faz um nó descer na árvore, realizando comparações e 
 * realizando trocas necessárias.
 *
 * Utilizando quando é removido, onde o último é jogado para
 * a primeira posição, e então essa função é chamada para
 * colocar ele no lugar correto, assim evitando realocação
 */
void bubble_down(priority_queue *p, int parent_index) {
    
    int child_index, i, min_index, temp;
    
    child_index = left_child(parent_index);
    
    min_index = parent_index;
    
    /**
     * Aqui é testado se o filho da esquerda ou da direita é maior que o pai
     */
    for (i = 0; i <= 1; i++) { 

        /**
         * Existe um filho
         */
        if ((child_index + i) <= p->n)
        { 
             /**
              * Verifica se o nó sendo verificado aqui é menor do que 
              * o menor nó da fila de prioridades
              */
            if (p->q[min_index].cost > p->q[child_index + i].cost)
            {
                min_index = child_index + i;
            }
        }

    }    
    
    /**
     * Se o menor indice encontrado na fila de prioridades
     * não for o indice passado pra função, faz um swap com
     * esse menor elemento
     */
    if (min_index != parent_index) {
        
        temp = p->q[min_index].cost;
        p->q[min_index].cost = p->q[parent_index].cost;
        p->q[parent_index].cost = temp;
        
        temp = p->q[min_index].x;
        p->q[min_index].x = p->q[parent_index].x;
        p->q[parent_index].x = temp;
        
        temp = p->q[min_index].y;
        p->q[min_index].y = p->q[parent_index].y;
        p->q[parent_index].y = temp;
        
        /**
         * Chama novamente, pra ver se é necessário fazer
         * mais trocas
         */
        bubble_down(p, min_index);
    }
    
}

/**
 * Remove o menor elemento da fila de prioridades
 */
void extract_min(priority_queue *p) {
    
    /**
     * Joga o menor elemento para variaveis globais
     */
    min = p->q[1].cost;
    x_min = p->q[1].x;
    y_min = p->q[1].y;
    
    /**
     * Traz o ultimo pra frente, para diminuir o tamanho da fila 
     * sem se preocupar com perda de dados
     */
    p->q[1].cost = p->q[p->n].cost;
    p->q[1].x = p->q[p->n].x;
    p->q[1].y = p->q[p->n].y;

    (p->n)--;
    
    /**
     * Então jogamos este elemento "para baixo" de volta
     */
    bubble_down(p, 1);
}

void pq_insert(priority_queue *p, int i, int x, int y) {
    
    /**
     * Incrementa elementos na fila
     */
    (p->n)++;
    p->q[p->n].cost = i;
    p->q[p->n].x = x;
    p->q[p->n].y = y;

    /**
     * É colocado na última posição, e então
     * é borbulhado para cima na posição correto
     */
    bubble_up(p, p->n);
}

/**
 * 
 *Algoritmo de Dijkstra. Ele pega o vértice não visitado com a menor distância,
 *calcula a distância por ele para cada vizinho não visitado, e atualiza a distância 
 *do vizinho, se menor marca visitados quando feito com os vizinhos.
 *
 */
void dijkstra(int N, int M, priority_queue *q) {

	/**
     * cima    baixo    dir      esq
     * direction é um vetor com direções x,y de modo que sempre pega o vizinho do vértice selecionado
     */

    int x, y, i, dx, dy, c, direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    x = 0;
    y = 0;

    /**
     * distance recebe o custo
     */
    distance[x][y] = cost[x][y];
    pq_insert(q, cost[x][y], x, y);
    
    /**
     * Enquanto houver elementos na fila de prioridades
     * realizamos uma série de relaxamentos das arestas, de acordo com o código
     */
    while (q->n) {
        
        /**
         * Remove o elemento com menor distância da fila
         */
        extract_min(q);

        /**
         * min é definido por uma varivel global
         */
        x = x_min;
        y = y_min;

        /**
         * set em vértice visitado nas posições x,y da lista
         */
        visited[x][y] = 1;
        
        /**
         * visita as em direction
         */
        for(i = 0; i < 4; i++) {

            /**
             * set em direction
             */
            dx = x + direction[i][0];
            dy = y + direction[i][1];
            
            /**
             * se há um elemento na matriz com o x e y acima
             * e se o mesmo não foi visitado já
             * verifica se dx é menor que o numero de linhas
             * verifica se dy é menor que o numero de colunas
             * e se a posição do dx,dy não foi visitada
             */
            if (dx >= 0 && dx < N && dy >= 0 && dy < M && !visited[dx][dy]) 
            {
                
                /**
                 * c recebe o custo do vértice na posição dx,dy
                 */
                c = cost[dx][dy];
                
                /**
                 * Atualiza distâncias caso tenham sido alteradas
                 */
                if (distance[x][y] + c < distance[dx][dy]) 
                {
                    
                    distance[dx][dy] = distance[x][y] + c;
                    
                    pq_insert(q, distance[dx][dy], dx, dy);
                    
                }
            }
        }
    }
}
