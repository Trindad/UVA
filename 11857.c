/**
 * =====================================================================================
 * Algoritmo em linguagem C++ para o problema 
 *
 *
 * Disciplina : Grafos
 * Alunos: Silvana Trindade, Maurício André Cinelli, Marivone Valentini
 * Janeiro de 2014
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Macro que inicializa um vetor a de n posições com o valor i
 */
#define initialize(i,a,n) for(i = 0;i < n; i++) a[i] = i

/**
 * Macro que computa o máximo entre dois valores
 */
#define max(a,b) (a > b) ? a : b

#define LIMIT 1000000

typedef struct edge {

    int from;
    int to;
    int weight;

} Edge;

static Edge edges[LIMIT];
static int path[LIMIT];

int getParent(int i,int *path);
int hasUnion(int u,int v,int* path);
void makeUnion(int u,int v,int* path);
int compareFunction(const void* u,const void* v);

int main(void)
{
    int totalVertices,totalEdges,i,nVerticesInPath,cost;

    scanf("%d %d",&totalVertices,&totalEdges);

    /**
     * Para este loop entrar, o scan acima ou o que se localiza
     * no final deste while devem encontrar um número valido para ou
     * vértices ou arestas
     *
     * Se encontrar 0 0, então significa final das entradas do problema
     */
    while(totalVertices || totalEdges)
    {   

        /**
         * Lê todos os pares de vértices que formam arestas
         * os dois primeiros números indicam os vértices de
         * inicio e destino, respectivamente, e o terceiro
         * número indica o peso da aresta.
         */
        for(i = 0;i < totalEdges;i++) {
            scanf("%d %d %d",&edges[i].from,&edges[i].to,&edges[i].weight);
        }

        /**
         * Inicializa o número de vértices passado por este caminho com zero
         */
        nVerticesInPath = 0;

        /**
         * Quick-sort interno do C (stdlib)
         */
        qsort(edges, totalEdges, sizeof(Edge), &compareFunction);

        /**
         * Inicializa o vetor de caminho com um número inválido,
         * já que se há 15 vértices, 16 jamais poderia ser um
         * vértice existente. Poderia ser -1. :)
         */
        initialize(i, path, totalVertices);

        /**
         * Inicializa custo máximo encontrado com 0 para cada caso de teste
         *
         * Custo aqui, apesar de estarmos em busca no maior custo, na realidade
         * representa o mínimo de distancia que a capacidade a bateria de um carro suporta 
         */
        cost = 0;

        /**
         * Enquanto não passar por todas as arestas e o número de vértices no
         * caminho for menor do que o total de vértices -1, então executa o loop
         */
        for(i = 0; i < totalEdges && nVerticesInPath < totalVertices-1; i++) {

            /**
             * Como queremos andar nas arestas, devemos pegar cada par de vértice
             * informado como aresta, e ver se já não está inclusa no caminho. 
             * Se não existir, adiciona esta aresta no caminho, e incrementa o custo
             * e o contador de vértices do caminho.
             */
            if(!hasUnion(edges[i].from,edges[i].to,path))
            {
                makeUnion(edges[i].from,edges[i].to,path);

                /**
                 * Incrementa numero de vértices no caminho, para que possa ser
                 * verificado depois se o numero de vértices passa por todos os
                 * vértices necessários
                 */
                nVerticesInPath++;
                
                /**
                 * Como há uma estação de recarga de bateria para o carro em cada cidade
                 * não precisamos levar em consideração o custo total, mas sim o maior
                 * custo (distancia) entre duas cidades, de modo a mostrar se o carro
                 * é ou não capaz de viajar nessas cidades.
                 */
                cost = max(cost,edges[i].weight);
            } 
        }
        
        /**
         * Como o problema diz que se independente do custo entre cidades, se não é
         * possivel viajar de uma cidade para todas as outras, então é impossível.
         */
        if(nVerticesInPath < totalVertices-1)
        {
            puts("IMPOSSIBLE");
        }
        else
        {
            printf("%d\n",cost);
        }

        /**
         * Se ler "0 0", é porque indica o fim das entradas
         * e o programa deve encerrar
         */
        scanf("%d %d",&totalVertices,&totalEdges);
    }

    return 0;
}


/**
 * `set` é como se fosse uma variavel de parentesco.
 * cada elemento guarda 'ele mesmo' se não possuir pai, 
 * caso contrário, contém qual é o pai de 'i'
 */
int getParent(int i,int *path) {

    if(i == path[i])
    {
        return i;
    }

    return ( path[i] = getParent(path[i],path) );
}


/**
 * Verifica se o pai de u é o mesmo pai de v,
 * o que significa que há uma ligação entre os dois
 */
int hasUnion(int u,int v,int* set){

    return getParent(u,set) == getParent(v,set);
}

void makeUnion(int u,int v,int* path){

    path[getParent(u,path)] = getParent(v,path);
}

/**
 * Função passada para a quick-sort, para que
 * seja usada como a função de comparação.
 *
 * ---
 * 
 * > 0  -- u > v
 * == 0 -- u = v
 * < 0  -- u < v
 */
int compareFunction(const void* u,const void* v) {

    return ((Edge*)u)->weight - ((Edge*)v)->weight;
}
