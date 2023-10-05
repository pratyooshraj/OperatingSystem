#include <stdio.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int id[n],t0[n], bt[n],t1[n], wt[n], tat[n];
    int tempid,tempt0, tempbt;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter id and burst time for each process: \n");
    for (int i = 0; i < n; i++)
    {
        printf("Process iD:\t");
        scanf("%d",&id[i]);

t0[i]=0;
        printf("Burst time:\t");
        scanf("%d", &bt[i]);
        printf("\n");
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(bt[j]>bt[j+1])
            {
                tempid=id[j];
                tempbt=bt[j];

                id[j]=id[j+1];
                bt[j]=bt[j+1];

                id[j+1]=tempid;
                bt[j+1]=tempbt;
            }
        }
    }

    // Calculate completion time for each process
    t1[0] = t0[0] + bt[0];
    for (int i = 1; i < n; i++)
    {
        t1[i] = t1[i - 1] + bt[i];
    }

    // Calculate waiting time for each process
    for (int i = 0; i < n; i++)
    {
        wt[i] = t1[i] - t0[i] - bt[i];
        avg_wt += wt[i];
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        tat[i] = t1[i] - t0[i];
        avg_tat += tat[i];
    }

    // Calculate average waiting and turnaround time
    avg_wt /= n;
    avg_tat /= n;

    printf("\nProcess|ArrivalTime|BurstTime|CompletionTime|WaitingTime|TurnaroundTime\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%7d|%11d|%9d|%14d|%11d|%14d\n", id[i], t0[i], bt[i], t1[i], wt[i], tat[i]);
    }

    printf("Average waiting time: %.2f\n", avg_wt);
    printf("Average turnaround time: %.2f\n", avg_tat);

    return 0;
}
