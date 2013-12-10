/*
--------------------------------------------------------------------------------------------------------------------
	Algoritmo em linguagem C padrão ANSI, para resolver o problema, tendo como caracteristica :

	A primeira linha do arquivo de entrada contém o número de casos de teste seu programa tem que processar.
 Cada teste é uma descrição floresta que consiste em duas partes:

1. Uma lista de arestas da árvore (um por linha, dado como um par não ordenado de letras maiúsculas
   delimitadas por uma linha de asteriscos).
2. A lista de pontos da árvore (estes serão dados em uma linha com um máximo de 26 correspondentes 
   às letras maiúsculas, A - Z)

*********************************************************************************************************************

Disciplina: Grafos

Alunos : Silvana Trindade

Data: 12-13
--------------------------------------------------------------------------------------------------------------------
*/

#include <stdio.h>

#define MAXIMUM 26 /*limite para alfabeto em letras maiusculas*/
#define TAM 100


/*
*	Funções auxiliares
*/
int getParente(int i, int *set);
/*
* Obtem parente/pai
*/
void fazUniao(int u,int v,int* set);
/*
* Faz a união dos vértices
*/

int main(void)
{

    int tree,acorns; /*numero de arvores e acorns*/
    int casos = 0;
    int i = 0,contador[MAXIMUM],set[MAXIMUM];
    char letras[TAM],buffer[TAM]; /*letras vetor para as letras*/

    scanf("%d",&casos); /*obtem o número de casos*/
    
	getchar();

	while(casos--)
    {

    	/*
    	*atribui valores para os vetores contador e set que irão
    	*/
        for(i = 0; i < MAXIMUM; i++)
        {
            set[i] = i; 
            contador[i] = 0;
        }
        while(gets(buffer) && buffer[0] != '*') { 

        	/*
        	* buffer[1] contem o primeiro vértice e o buffer[3] o segundo vértice de conexão das arestas
        	* faz a união entre os vértices até encontrar * aí vai para o 
        	*/
            fazUniao(buffer[1]-'A',buffer[3]-'A',set);
        }

        /*
        * Lê uma linha de texto digitado no teclado e a armazena em letras
        * verifica e incrementa contador conforme o numero de caracteres diferentes de vírgula
        */

        gets(letras); 
        
        for(i = 0; letras[i]; i++) { 

            if(letras[i] != ',') 
            {
               contador[getParente(letras[i]-'A',set)]++;
            }
        }
        tree = acorns = 0;

        /*
        * Conta o numero de árvores que a floresta possui e o número de acorns
        */
        for(i = 0; i < MAXIMUM; i++) {

            if( contador[i] > 1)
            {
                tree++; /* incrementa o número de árvores caso a árvore tiver filhos */
            }
            else if(contador[i] == 1) 
            {
                acorns++; /*incrementa o número de acorns, caso um vértice for sozinho*/
            }
        }
        printf("There are %d tree(s) and %d acorn(s).\n",tree,acorns);
    }
    return 0;
}

int getParente(int i, int *set)
{
    if(i == set[i])
    {
        return i;
    }
    else
    {
        return (set[i] = getParente(set[i],set));
    }
}

void fazUniao(int u,int v,int* set)
{
    set[getParente(u,set)] = getParente(v,set);
}
