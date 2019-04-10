/*******************************************************
Name: Luis Mendiola
Professor: Leticia Rabor
Class: CS433
Date: April 1, 2019

Program: This is an interactive program that implements
	 the banker's algorithm.
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banker.h"
//int request_resources(int cost_num, int request);
//void release_resources(int cost_num, int request);
int main(int argc, char* argv[])
{		
	// user's input size, command size, size of arr[], costumer number, and response to request
	int SIZE = 13, cmd_size = 3, arr_size = 4, cost_num, response;
	/*
	- str[] contains the user's input 
	- str_copy[] is the copy of str[]
	- tok[7] holds the tokens of str[]
	- cmd[] contains the command "RQ", "RL", or "*"
	- ch[] contains "y" to continue program or another character to exit
	- res_arr[] contains the resources being requested or released
	*/ 
	char str[SIZE], str_copy[SIZE], tok[7] = "", cmd[cmd_size], ch[cmd_size], res_arr[arr_size];
	char delim[] = " ";// space is the delimiter
	char *ptr = NULL; // pointer to user's input
	int str_len; // length of user's input
	int count;// number of arguments passed on the command line
	FILE *infile = NULL;// pointer to a file
	int n = NUMBER_OF_COSTUMERS;
	int m = NUMBER_OF_RESOURCES;
	int i, j;// used to traverse data
	int arr[arr_size-1], res;// holds the four different resources and res holds a resource
	//int available[m];// available resources
	//int maximum[n][m];// maximum demand of resources 

	/* INTRODUCTION */
	printf("\tWelcome! This program implements the banker's algorithm.\n\n");

	/* Ask user to continue or not */
	printf("\t\tDo you wish to continue?\n"); 
	printf("\t\tEnter 'y' to continue or any other charachter exit.\n\n");
	fgets(ch, cmd_size, stdin);
	if(ch[0] == 'y')// if user enters 'y' continue program
	{	
				
		printf("\t\tYou have entered %d arguments\n", argc);
		printf("\t\tThe following are the arguments:\n");
		for(count = 0; count < argc; count++)
			printf("\t\targv[%d]: %s\n", count+1, argv[count]);  

		/* store input from command line into available array */
		for(count = 0; count < m; count++)
			available[count] = atoi(argv[count+1]);
		printf("\n");
		/* print the contents of the available array */
		printf("\t\tResources available[]:\n");
		for(count = 0; count < m; count++)
			printf("\t\t%d\n", available[count]);
		printf("\n");
		/* allocate resources */
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < m; j++)
			{
				printf("\t\tAllocation for resource[%d][%d]:", i+1, j+1);
				scanf("%d", &allocation[i][j]);
			}
		}

		/* read file and store into the maximum array */
		infile = fopen("requestfile.txt", "r");
		if(infile == NULL)// return 0 if file doesn't exist or its empty
		{
			printf("Error opening file.\n");
			return 0;
		}
		else// otherwise read file
		{
			printf("\t\tmaximum[][]:\n");
			for(i = 0; i < n; i++)
			{
				printf("\t\t");
				for(j = 0; j < m; j++)
				{
					fscanf(infile, "%d,", &maximum[i][j]);
					printf("%d ", maximum[i][j]);
				}
				printf("\n");
			}	
		}
		fclose(infile);

		printf("\t\tDo you wish to request, release, or view the resources?\n"); 
		printf("\t\tEnter 'y' to continue or any other character to exit.\n");
		fgetc(stdin);
		fgets(ch, cmd_size, stdin);

		while(ch[0] == 'y')// while the user enters 'y'
		{ 	
			/* ask user to enter a command */
			printf("\n");
			printf("\t\tPlease enter a command (RQ,RL,or *):\n");
			printf("\t\t\"RQ\" - used to request resources\n");
			printf("\t\t\"RL\" - used to release resources\n");
			printf("\t\t\"*\" - used to print the values in\n");
			printf("\t\tthe available, maximum, allocation and need arrays\n");
			printf("\n");
			printf("\t\tUse the following format: \"cmd costumer# R1 R2 R3 R4\"\n");
			fgets(str, SIZE, stdin);
			strcpy(str_copy, str);// copy str into str_cpy

			ptr = strtok(str_copy, delim);// tokenize the user's input
			while(ptr != NULL)
			{
				strcat(tok, ptr);// concatanate the tokens
				//printf("'%s'", ptr);
				ptr = strtok(NULL, delim);
			
			}
			

			/* retrieve command */
			memset(cmd, '\0', sizeof(cmd));// clear cmd[] array
			strncpy(cmd, tok, 2);// copy RQ, RL or * from tok[] to cmd[]
		
	
			if(strcmp(cmd, "RQ") == 0)// if the user enters command to request
			{
				printf("\t\tYou have entered \"RQ\"\n");
				strncpy(res_arr, tok + 2, 5);// extract the remaining of tok[]
				tok[0] = '\0';// clear tok[] array
				str_len = sizeof(res_arr) / sizeof(res_arr[0]);
				cost_num = res_arr[0] - '0';// get the costumer number
				//printf("\t\tcostumer number is: %d\n", cost_num);
				for(i = 0; i < str_len ; i++)// convert string of numbers to int
					arr[i] = res_arr[i+1] - '0';
				printf("\t\tCostumer %d has requested:\n", cost_num);
				for(i = 0; i < str_len; i++)
					printf("\t\t%d instances from resource %d\n", arr[i], i+1);
				printf("\n");
				//call the request function
				response = request_resources(cost_num, arr);
				if(response == 0)
					printf("\t\tRequest granted. System is in a safe state.\n");
				else if(response == - 1)
				{
					printf("\t\tRequest denied. System is unsafe.\n");
					//break;// exit
				}
				else// otherwise do nothing	
					return 0;
			}
			else if(strcmp(cmd, "RL") == 0)// if the user enters command to release
			{
				printf("\t\tYou have entered \"RL\"\n");
				
				strncpy(res_arr, tok + 2, 5);// extract the remaining of tok[]
				tok[0] = '\0';// clear tok[] array
				str_len = sizeof(res_arr) / sizeof(res_arr[0]);
				cost_num = res_arr[0] - '0';// get the costumer number
				//printf("\t\tcostumer number is %d\n", cost_num);
				for(i = 0; i < str_len ; i++)// convert string of numbers to int
					arr[i] = res_arr[i+1] - '0';
				printf("\t\tCostumer %d is releasing:\n", cost_num);
				for(i = 0; i < str_len; i++)
					printf("\t\t%d instances from resource %d\n" , arr[i], i);
				printf("\n");
				release_resources(cost_num, arr);//call the release function
			}
			else if(cmd[0] == '*')// if the user enters command to print
			{	
				tok[0] = '\0';// clear tok[] array
				printf("\t\tYou have entered \"*\"\n");
				printf("\t\tPrinting available, maximum, allocation, and need\n");
				printf("\t\tmatrices ...\n");
				/* print available matrix */
				printf("\t\tavailable[]:\n");
				printf("\t\t");
				for(i = 0; i < m; i++)
					printf("%d ", available[i]);
				printf("\n");
				/* print maximum matrix */
				printf("\t\tmaximum[][]:\n");
				for(i = 0; i < n; i++)
				{
					printf("\t\t");
					for(j = 0; j < m; j++)
						printf("%d ", maximum[i][j]);
					printf("\n");
				}	
				/* print allocation matrix */
				printf("\t\tallocation[][]:\n");
				for(i = 0; i < n; i++)
				{
					printf("\t\t");
					for(j = 0; j < m; j++)
						printf("%d ", allocation[i][j]);
					printf("\n");
				}
				/* print need matrix */
				printf("\t\tneed[][]:\n");
				for(i = 0; i < n; i++)
				{
					printf("\t\t");
					for(j = 0; j < m; j++)
						printf("%d ", need[i][j]);
					printf("\n");
				}

			}
			else// otherwise print error message
			{
				printf("\t\tcmd != \"RQ\", \"RL\", or \"*\"\n");
			}
			/* prompt user to continue or exit */
			printf("\n");
			printf("\t\tDo you wish to continue requesting, releasing, or viewing\n");
			printf("\t\tthe resources?\n");
			printf("\t\tEnter 'y' to continue or any other character to exit.\n");
			fgetc(stdin);//clear input stream
			fgets(ch, cmd_size, stdin);
		}
		printf("\t\tGoodbye!\n");
	}
	else//otherwise exit the program
	{	
		printf("\t\tGoodbye!\n\n");
		return 0;
	}

}//END OF PROGRAM
