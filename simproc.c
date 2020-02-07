#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simproc.h"

struct simstat *
sim_sjf(int scenario)
{
	printf("Running SJF new scenario...\n");
	return NULL;
}

void swap(process *a, process *b)
{
    process temp = *a;
    *a = *b;
    *b = temp;
}


int maxim ( int a, int b) {
    if ( a > b )
        return a;
    return b;
}

void coppyProcesessTo(process here[], process from[], int numberOfProcesses)
{
    int i;

    for (i = 0; i < numberOfProcesses; i++){
        here[i] = from[i];
    }
}

void sortByArrivalTime(process P[], int numberOfProcesses)
{
    int i, j;

    for (i = 0; i < numberOfProcesses - 1; i++){
        for (j = i + 1; j < numberOfProcesses; j++){
            if (P[i].arrivalTime > P[j].arrivalTime){
                swap(&P[i], &P[j]);
            }
        }
    }
}

void sortByBurstTime(process P[], int numberOfProcesses)
{
    int i, j;

    for (i = 0; i < numberOfProcesses - 1; i++)
    {
        for (j = i + 1; j < numberOfProcesses; j++)
        {
            if (P[i].burstTime > P[j].burstTime)
            {
                swap(&P[i], &P[j]);
            }
        }
    }
}

void showInitialGrid(process P[], int numberOfProcesses)
{
    int i;

    printf("\nProces Name\tBurst Time\tArrival Time\tPriority\n");

    for (i = 0; i < numberOfProcesses; i++){
        printf("\n  %s\t\t %d\t\t %d\t\t %d", P[i].procesName, P[i].burstTime, P[i].arrivalTime, P[i].priority);
    }
}

void shoWGridForWTAndAT(process P[], int numberOfProcesses)
{
    int i;

    printf("\nProces Name\tWaiting Time\tTurn Around Time\n");

    for (i = 0; i < numberOfProcesses; i++){
        printf("\n  %s\t\t %d\t\t %d", P[i].procesName, P[i].waitingTime, P[i].turnAroundTime);
    }
}

void showGanttChart(process P[], int numberOfProcesses)
{
    int i, waitingTime;
    printf("\n\n GANTT CHART\n ");

    for (i = 0; i < numberOfProcesses; i++)
        printf("   %s   ", P[i].procesName);
    printf("\n 0\t");
    for (i = 1; i <= numberOfProcesses; i++){
        waitingTime = waitingTime + P[i - 1].burstTime;
        printf("%d\t", waitingTime);
    }
}

void readTheProcesses(process P[], int * numberOfProcesses)
{
    int i;

    printf("\nHow many processes will you introduce?\n");
    scanf("%d", &i);
    * numberOfProcesses = i;

    for (i = 0; i < *numberOfProcesses; i++){
        printf("\n PROCESS [%d]", i + 1);

        printf(" Enter process name : ");
        char * s_aux = (char *) malloc ( 30 * sizeof(char));
        scanf("%s", s_aux);
        strcpy ( P[i].procesName, s_aux);
        free ( s_aux );
        printf(" Enter burst time : ");
        scanf("%d", &P[i].burstTime);
        printf(" Enter arrival time : ");
        scanf("%d", &P[i].arrivalTime);
        printf(" Enter priority : ");
        scanf("%d", &P[i].priority);
    }
    showInitialGrid(P, *numberOfProcesses);
}

void FCFS(process P[], int numberOfProcesses)
{

    int i, j;
    process localProcesses[100];
    coppyProcesessTo(localProcesses, P, numberOfProcesses );
    sortByArrivalTime(localProcesses, numberOfProcesses);
    showInitialGrid(localProcesses, numberOfProcesses);

    int totalTurnAround ;
    int totalWaitingTime = localProcesses[0].waitingTime = 0;
    if (localProcesses[0].burstTime - localProcesses[0].arrivalTime < 0) 
        totalTurnAround = localProcesses[0].turnAroundTime = localProcesses[0].burstTime - localProcesses[0].arrivalTime;
    else totalTurnAround = localProcesses[0].turnAroundTime = localProcesses[0].burstTime + localProcesses[0].waitingTime;


    for (i = 1; i < numberOfProcesses; i++){
        int lastTimeAccumulated = localProcesses[i - 1].burstTime + localProcesses[i - 1].arrivalTime + localProcesses[i - 1].waitingTime;
        localProcesses[i].waitingTime = maxim ( lastTimeAccumulated - localProcesses[i].arrivalTime, 0 );
        totalWaitingTime += localProcesses[i].waitingTime;

        localProcesses[i].turnAroundTime = localProcesses[i].waitingTime + localProcesses[i].burstTime;
        totalTurnAround = localProcesses[i].turnAroundTime;
    }

    shoWGridForWTAndAT(localProcesses, numberOfProcesses);
    showGanttChart(localProcesses, numberOfProcesses);
    printf("\n\nTotal waiting time = %d\nAverage waiting time = %0.2f\nAverage turn-around = %0.2f", totalWaitingTime, ((1.0)*totalWaitingTime/numberOfProcesses), ((1.0)*totalTurnAround/numberOfProcesses));
}

void RoundRobin(process P[], int numberOfProcesses)
{
    int i, j, quantumTime, processNum = 0, weAreDone = 0, totalTime = 0, processesFinished = 0, totalTurnAround = 0, totalWaitingTime = 0;
    process localProcesses[100];
    int processIsDone[100] = {0};
    coppyProcesessTo(localProcesses, P, numberOfProcesses);
    sortByArrivalTime(localProcesses, numberOfProcesses);
    showInitialGrid(localProcesses, numberOfProcesses);
    printf("\n Enter the quantum time :\n ");
		char sir[40];
    scanf("%s", sir);
		if ( sir[0] <'0' || sir[0] > '9')
			quantumTime = 3;
		else quantumTime = atoi (sir);

    printf ( "Quantum time : %d\n", quantumTime);
    while(weAreDone == 0){
        if (processNum > numberOfProcesses - 1){
            processNum = 0;
        }

        if (localProcesses[processNum].burstTime > 0){
            printf("   %d  %s", totalTime, localProcesses[processNum].procesName);
        }

        int quantumStat = 0;

        while (quantumStat < quantumTime && localProcesses[processNum].burstTime > 0){
            quantumStat++; totalTime++; localProcesses[processNum].burstTime--;
        }

        if (localProcesses[processNum].burstTime < 1 && processIsDone[processNum] == 0){
            localProcesses[processNum].waitingTime = totalTime - localProcesses[processNum].arrivalTime - P[processNum].burstTime;
            localProcesses[processNum].turnAroundTime = totalTime - localProcesses[processNum].arrivalTime;
            processesFinished++; processIsDone[processNum] = 1;
            totalWaitingTime += localProcesses[processNum].waitingTime;
            totalTurnAround += localProcesses[processNum].turnAroundTime;
        }

        if (processesFinished == numberOfProcesses){
            weAreDone = 1;
            printf("    %d", totalTime);
        }


        processNum++;
    }

    printf("\n\nTotal waiting time = %d\nAverage waiting time = %0.2f\nAverage turn-around = %0.2f", totalWaitingTime, ((1.0) * totalWaitingTime / numberOfProcesses), ((1.0) * totalTurnAround / numberOfProcesses));
}




void SJF_nonP(process pvec[], int numberOfProcesses)
{

	int n = numberOfProcesses;

    int i, j, k, total_time, x, totalWaitingTime, totalTurnAround, min_burstTime;
    process t[100], taux;
    total_time = 0;

    coppyProcesessTo(t, pvec, numberOfProcesses);

    sortByArrivalTime(t, numberOfProcesses);
    sortByBurstTime(t, numberOfProcesses);

    showInitialGrid(t, numberOfProcesses);




    if (t[0].burstTime - t[0].arrivalTime < 0) 
        totalTurnAround = t[0].turnAroundTime = t[0].burstTime - t[0].arrivalTime;
    else totalTurnAround = t[0].turnAroundTime = t[0].burstTime + t[0].waitingTime;





    totalWaitingTime = t[0].waitingTime = 0;
    totalTurnAround = t[0].turnAroundTime = maxim ( t[0].burstTime - t[0].arrivalTime, 0);

    for (i = 1; i < n; i++)
    {
        t[i].waitingTime = maxim ((t[i - 1].burstTime + t[i - 1].arrivalTime + t[i - 1].waitingTime) - t[i].arrivalTime, 0);
        t[i].turnAroundTime = (t[i].waitingTime + t[i].burstTime);
        totalWaitingTime += t[i].waitingTime;
        totalTurnAround += t[i].turnAroundTime;
    }

    shoWGridForWTAndAT(t, numberOfProcesses);
    showGanttChart(t, numberOfProcesses);

    printf("\n\nTotal waiting time = %d\nAverage waiting time = %0.2f\nAverage turn-around = %0.2f", totalWaitingTime, ((1.0) * totalWaitingTime / numberOfProcesses), ((1.0) * totalTurnAround / numberOfProcesses));
}

void SJF_P(process pvec[], int n)
{

	int  numberOfProcesses = n;
    int i, j, k, total_time, aux[100], b[101], c_time, totalWaitingTime, totalTurnAround, min_burstTime;
    process t[100];
    total_time = 0;
    coppyProcesessTo(t, pvec, numberOfProcesses);
    sortByArrivalTime(t, numberOfProcesses);

    for (i = 0; i < n; i++){
        aux[i] = t[i].burstTime;
        total_time += pvec[i].burstTime;
    }


    i = j = 0;
    totalWaitingTime = totalTurnAround = 0;
    printf("\n GANTT CHART\n\n %d %s", i, t[i].procesName);

    for (c_time = 0; c_time < total_time; c_time++)
    {
        if (aux[i] > 0 && t[i].arrivalTime <= c_time)
            aux[i]--;

        if (i != j)
            printf("  %d %s", c_time, t[i].procesName);

        if (aux[i] <= 0 && t[i].priority != 1)
        {
            t[i].priority = 1;
            t[i].waitingTime = (c_time + 1) - t[i].burstTime - t[i].arrivalTime;
            t[i].turnAroundTime = (c_time + 1) - t[i].arrivalTime;
            totalWaitingTime += t[i].waitingTime;
            totalTurnAround += t[i].turnAroundTime;
        }
        j = i;
        min_burstTime = 9999;
        for (k = 0; k < n; k++)
            if (t[k].arrivalTime <= (c_time + 1) && t[k].priority != 1)
                if( min_burstTime > aux[k] && min_burstTime != aux[k])
                {
                    min_burstTime = aux[k];
                    i = k;
                }
    }

    printf("\t%d", c_time);

    printf("\n\nTotal waiting time = %d\nAverage waiting time = %0.2f\nAverage turn-around = %0.2f", totalWaitingTime, ((1.000) * totalWaitingTime / numberOfProcesses), ((1.000) * totalTurnAround / numberOfProcesses));
}
