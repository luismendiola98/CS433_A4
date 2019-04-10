#ifndef BANKER_H
#define BANKER_H

#define NUMBER_OF_COSTUMERS 5
#define NUMBER_OF_RESOURCES 4
/***************
DATA STRUCTURES
****************/
/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/* the maximum demand of each costumer */
int maximum[NUMBER_OF_COSTUMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each costumer */
int allocation[NUMBER_OF_COSTUMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each costumer */
int need[NUMBER_OF_COSTUMERS][NUMBER_OF_RESOURCES];

/*******************
FUNCTION PROTOTYPES
********************/
int request_resources(int costumer_num, int request[]);

void release_resources(int costumer_num, int release[]);

#endif
