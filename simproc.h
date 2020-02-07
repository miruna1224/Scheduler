#ifndef SIMPROC_H
#define SIMPROC_H

struct simstat {
	int avgwait;
	int turnaround;
};

typedef struct processes
{
    char procesName[30];
    int responseTime;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnAroundTime;
    int priority;

} process;

struct simstat * sim_sjf(int);

void readTheProcesses(process[], int * );
void FCFS(process[], int);
void RoundRobin(process[] , int);
void SJF_nonP( process[], int);
void SJF_P(process[], int);



#endif
