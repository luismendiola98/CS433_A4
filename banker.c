
#include "banker.h"

/* This function will request resources for the costumer */
int request_resources(int costumer_num, int request[])
{
	int i, j, k, n = NUMBER_OF_COSTUMERS, m = NUMBER_OF_RESOURCES;// used to traverse arrays
	int finish[n];// finished costumers
	int safe[n];// safe sequence
	int work[1][m];// copy of available resources
	int count = 0, pflag = 0, flag = 0;

	/* calculate need matrix */ 
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			need[i][j] = maximum[i][j] - allocation[i][j]; 
	/* set finish[] array to false */
	for(i = 0; i < n; i++)
		finish[i] = 0;
	/* copy the available resources */
	for(i = 0; i < m; i++)
		work[0][i] = available[i];
	/* while the costumers are not finished 
	or the system is not in a safe state */
	//for(k = 0; k < n; k++)
	//{
		for(i = 0; i < n; i++)
		{
			if(finish[i] == 0)// if the current costumer is not finished
			{
				flag = 0;
				for(j = 0; j < m; j++)
				{
					if(need[i][j] > work[0][j])// if needed resources > current
						flag = 1;
				}
				// if current costumer is not finished
				// and needed resources < resources in work[]
				if(flag == 0 && finish[i] == 0)
				{
					for(j = 0; j < m; j++)
						work[0][j] += allocation[i][j];
					finish[i] = 1; // current costumer is finished
					pflag++;
					safe[count++] = i;
				}
			}

		}
		if(pflag == n)// system is in a safe state
			return 0;
		else// system is in a unsafe state
			return -1;
	//}
	//return -1;// system is not in a safe state
	
} 

/* This function will release the resources for the costumer */
void release_resources(int costumer_num, int release[])
{




}
