#include <stdio.h>

#define MAX_p 10
#define MAX_r 3

void cal_need_mat(int need[][MAX_r], int max[][MAX_r], int alc[][MAX_r], int n)
{
	int i,j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < MAX_r; j++)
        {
            need[i][j] = max[i][j] - alc[i][j];
        }
    }
}

int isSafe(int ava[], int need[][MAX_r], int alc[][MAX_r], int n)
{
    int work[MAX_r];
    int finish[MAX_p] = {0};
    int safeS[MAX_p];
    int count = 0;
	int i,k;
    for (i = 0; i < MAX_r; i++)
    {
        work[i] = ava[i];
    }

    while (count < n)
    {
        int found = 0;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < MAX_r; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == MAX_r)
                {
                    for (k = 0; k < MAX_r; k++)
                    {
                        work[k] += alc[i][k];
                    }
                    safeS[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    if (count < n)
    {
        printf("Unsafe state: No safe sequence ava.\n");
        return 0;
    }
    printf("Safe sequence: ");
    for (i = 0; i < n - 1; i++)
    {
        printf("P%d -> ", safeS[i]);
    }
    printf("P%d\n", safeS[n - 1]);

    return 1;
}

int rqr(int pID, int rq[], int ava[], int need[][MAX_r], int alc[][MAX_r], int n)
{
	int i;
    for (i = 0; i < MAX_r; i++)
    {
        if (rq[i] > need[pID][i])
        {
            printf("Error: Process P%d rqed more r than its maximum claim.\n", pID);
            return 0;
        }
        if (rq[i] > ava[i])
        {
            printf("Process P%d is waiting. Not enough r ava.\n", pID);
            return 0;
        }
    }

    for (i = 0; i < MAX_r; i++)
    {
        ava[i] -= rq[i];
        alc[pID][i] += rq[i];
        need[pID][i] -= rq[i];
    }

    if (isSafe(ava, need, alc, n))
    {
        printf("rq granted. r allocated to Process P%d.\n", pID);
        return 1;
    }
    else
    {
        for (i = 0; i < MAX_r; i++)
        {
            ava[i] += rq[i];
            alc[pID][i] -= rq[i];
            need[pID][i] += rq[i];
        }
        printf("rq denied. alc would lead to an unsafe state.\n");
        return 0;
    }
}

int main()
{
    int n,i,j;
    printf("Enter the number of p: ");
    scanf("%d", &n);

    int max[MAX_p][MAX_r];
    int alc[MAX_p][MAX_r];
    int ava[MAX_r];

    printf("Enter the maximum number of instances of each resource needed for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process P%d:\n", i);
        for (j = 0; j < MAX_r; j++)
        {
            printf("Resource %c: ", 'A' + j);
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the currently allocated number of instances of each resource:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process P%d:\n", i);
        for (j = 0; j < MAX_r; j++)
        {
            printf("Resource %c: ", 'A' + j);
            scanf("%d", &alc[i][j]);
        }
    }

    printf("Enter the number of instances of ava r:\n");
    for (i = 0; i < MAX_r; i++)
    {
        printf("Resource %c: ", 'A' + i);
        scanf("%d", &ava[i]);
    }

    int need[MAX_p][MAX_r];
    cal_need_mat(need, max, alc, n);

    int pID;
    int rq[MAX_r];

    printf("Enter the process id (0 to %d) that is making the rq: ", n - 1);
    scanf("%d", &pID);

    printf("Enter the number of instances of each resource rqed by Process P%d:\n", pID);
    for (i = 0; i < MAX_r; i++)
    {
        printf("Resource %c: ", 'A' + i);
        scanf("%d", &rq[i]);
    }

    rqr(pID, rq, ava, need, alc, n);

    return 0;
}
