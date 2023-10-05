#include<stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    // Make a copy of burst times bt[] to store remaining burst times.
    int rem_bt[n];
    int i;

    for (i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0; // Current time

    // Keep traversing processes in round robin manner until all of them are not done.
    while (1) {
        int done = 1; // Assume all processes are done

        // Traverse all processes one by one repeatedly
        for (i = 0; i < n; i++) {
            // If burst time of a process is greater than 0 then only need to process further
            if (rem_bt[i] > 0) {
                done = 0; // There is a pending process

                if (rem_bt[i] > quantum) {
                    // Increase the value of t, i.e., shows how much time a process has been processed
                    t += quantum;

                    // Decrease the burst_time of the current process by quantum
                    rem_bt[i] -= quantum;
                }
                else {
                    // Increase the value of t, i.e., shows how much time a process has been processed
                    t = t + rem_bt[i];

                    // Waiting time is current time minus time used by this process
                    wt[i] = t - bt[i];

                    // As the process gets fully executed, make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }
        }

        // If all processes are done
        if (done == 1)
            break;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time by adding bt[i] + wt[i]
    int i;
    for (i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0, i;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, quantum);

    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    printf("Process\tBurst\tWaiting\tTAT\n");

    // Calculate total waiting time and total turn around time
    for (i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d\t %d\t %d\t %d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}

// Driver code
int main() {
    // process id's
    int processes[] = { 1, 2, 3,4,5 };
    int n = sizeof(processes) / sizeof(processes[0]);

    // Burst time of all processes
    int burst_time[] = {6,5,4,3,3 };

    // Time quantum
    int quantum = 3;

    findavgTime(processes, n, burst_time, quantum);

    return 0;
}
