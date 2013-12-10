/*

	Algoritmo em linguagem C padrão ANSI, para resolver o problema Wedding of Sultan , onde 
	Utilizando o método DFS() para visitar o Grafo.
	Solução :
		--> Primeiro faz push()
		--> Segunda faz pop()

Disciplina: Grafos
Alunos : Silvana Trindade, Maurício Andrá Cinelli e Marivone Valentin
e-mails: syletri@gmail.com, mauricio.andre.cinelli,marivonevalentini@yahoo.com.br
Data: 04-12-13

*/

#include <stdio.h>
#include <string.h>

#define LIMIT 128

int main(void) {

    int t, cases = 0, i;

    scanf("%d", &t); /* quantos casos de teste irá ter */
    
    while(t--) {

        char s[105];
        int ans[LIMIT] = {}, stack[LIMIT];
        int stackIdx = -1;

        scanf("%s", s); /*leitura da string*/

        /*
        * Empilha os caracteres 
        */
        for(i = 0; s[i]; i++) { 

            if(stackIdx < 0 || stack[stackIdx] != s[i]) 
            {
            	stack[++stackIdx] = s[i]; /*Recebe o valor em interiro equivalente ao caractere ASCII*/
                
            	ans[(int)s[i]]++; /*armazena o numero de vezes que passou pelo vértice*/
            }
            else
            {
                stackIdx--;

                if(stackIdx >= 0)
                {
                   ans[stack[stackIdx]]++; 
                }
            }
        }
        
        printf("trilha: %d s: %c",ans[(int)s[0]]--,s[0]);

        printf("Case %d\n", ++cases); /*imprime numero do caso*/

        for(i = 'A'; i <= 'Z'; i++) { /*percorre o for*/

            if(ans[i]) /* se existir nesse caso a trilha com o valor de i então imprime*/
            {
                printf("%c = %d\n", i, ans[i]); /*imprime nome e numero de trilhas */
            }
        }
    }
    return 0;
}
