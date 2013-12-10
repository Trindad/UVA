#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(void)
{

	int n = 0;

	while (scanf("%d", &n) == 1 && n) {

		int numeros[3000], jolly[3000];

		int i = 0;

		for (i = 0; i < n; i++)
		{
			scanf("%d", &numeros[i]);
			jolly[i] = 0;
		}

		int z = 0;

		for (; z < n-1; z++) {

			int val = abs(numeros[z + 1] - numeros[z]);
			if ( val >= 0 && val <= (n - 1)) {
				jolly[val] = 1;
			}
		}

		int sum = 0, k ;

		for (k = 0; k < n; k++) {
			sum = sum + jolly[k];
		}

		if (sum == n - 1)
		{
			printf("Jolly\n");
		} 
		else
		{
			printf("Not jolly\n");
		}

	}
	return 0;

}
