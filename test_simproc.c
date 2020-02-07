#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simproc.h"




int numberOfProcesses = 0;
process P[100];


int main()
{
	// struct simstat *stats = malloc(sizeof(*stats));

	// int scenario = 0;
	// stats = sim_sjf(scenario);

	// return 0;

    int weStillRead = 1;

    while (weStillRead == 1){
        printf("\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n");
        printf("\n Chose one simpatikule:\n");
        printf("\n 0. Enter process data.");
        printf("\n 1. FCFS");
        printf("\n 2. SJF (Pre-emptive)");
        printf("\n 3. SJF (Non Pre-emptive)");
        printf("\n 4. Round Robin");
        printf("\n 5. Exit ");
        printf("\n 6. Initialize scenario\n \nSelect : ");
        int chose;
        scanf("%d", &chose);
        if (chose == 0){
            readTheProcesses( P, &numberOfProcesses );
        }
        else if (chose == 1){
            FCFS(P, numberOfProcesses);
        }
        else if (chose == 2){
            SJF_P(P, numberOfProcesses);
        }
        else if(chose == 3){
            SJF_nonP(P, numberOfProcesses);
        }
        else if (chose == 4){
            RoundRobin(P, numberOfProcesses);
        }
        else if (chose == 5){
            weStillRead = 0;
            printf("\n\nThe program is DED now X0\n\n");
        }
        else if (chose == 6 ){
	        printf("\n Chose one to initialize the scenario for:");
	        printf("\n 1. FCFS");
	        printf("\n 2. SJF (Pre-emptive)");
	        printf("\n 3. SJF (Non Pre-emptive)");
	        printf("\n 4. Round Robin\n \nSelect : ");

	        int ch;
	        scanf("%d", &ch);
	        if ( ch == 1 ){
	        	numberOfProcesses = 4;
	        	P[0].arrivalTime = 0;
	        	P[0].burstTime = 5;
	        	P[0].priority = 1;
	        	strcpy ( P[0].procesName, "p1");

	        	P[1].arrivalTime = 1;
	        	P[1].burstTime = 3;
	        	P[1].priority = 2;
	        	strcpy ( P[1].procesName, "p2");


	        	P[2].arrivalTime = 2;
	        	P[2].burstTime = 8;
	        	P[2].priority = 3;
	        	strcpy ( P[2].procesName, "p3");


	        	P[3].arrivalTime = 3;
	        	P[3].burstTime = 6;
	        	P[3].priority = 4;
	        	strcpy ( P[3].procesName, "p4");
	        }
	        else{
	        	if ( ch == 2){

	        		numberOfProcesses = 4;
		        	P[0].arrivalTime = 5;
		        	P[0].burstTime = 2;
		        	P[0].priority = 1;
		        	strcpy ( P[0].procesName, "p1");

		        	P[1].arrivalTime = 2;
		        	P[1].burstTime = 4;
		        	P[1].priority = 2;
		        	strcpy ( P[1].procesName, "p2");


		        	P[2].arrivalTime = 0;
		        	P[2].burstTime = 6;
		        	P[2].priority = 3;
		        	strcpy ( P[2].procesName, "p3");


		        	P[3].arrivalTime = 1;
		        	P[3].burstTime = 4;
		        	P[3].priority = 4;
		        	strcpy ( P[3].procesName, "p4");

	        	}
	        	else {
	        		if ( ch == 3 ){

		        		numberOfProcesses = 4;
			        	P[0].arrivalTime = 0;
			        	P[0].burstTime = 100;
			        	P[0].priority = 1;
			        	strcpy ( P[0].procesName, "p1");

			        	P[1].arrivalTime = 2;
			        	P[1].burstTime = 5;
			        	P[1].priority = 2;
			        	strcpy ( P[1].procesName, "p2");


			        	P[2].arrivalTime = 2;
			        	P[2].burstTime = 10;
			        	P[2].priority = 3;
			        	strcpy ( P[2].procesName, "p3");


			        	P[3].arrivalTime = 10;
			        	P[3].burstTime = 25;
			        	P[3].priority = 4;
			        	strcpy ( P[3].procesName, "p4");
	        		}
	        		else{

		        		numberOfProcesses = 4;

			        	P[0].arrivalTime = 0;
			        	P[0].burstTime = 5;
			        	P[0].priority = 1;
			        	strcpy ( P[0].procesName, "p1");

			        	P[1].arrivalTime = 1;
			        	P[1].burstTime = 3;
			        	P[1].priority = 2;
			        	strcpy ( P[1].procesName, "p2");


			        	P[2].arrivalTime = 2;
			        	P[2].burstTime = 8;
			        	P[2].priority = 3;
			        	strcpy ( P[2].procesName, "p3");


			        	P[3].arrivalTime = 3;
			        	P[3].burstTime = 6;
			        	P[3].priority = 4;
			        	strcpy ( P[3].procesName, "p4");
	        		}
	        	}
	        }
        }
    }
    return 0;
}
