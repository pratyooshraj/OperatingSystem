#include <stdio.h>
int main()
{
    int n, m, i, j, k,y=0;
    int alloc[10][5],max[10][5],need[10][5], P[10],avail[10];
    printf("\n Enter the number of resources : ");
    scanf("%d", &m);
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);
    int f[10], ans[10], ind = 0;// Number of resources
    printf("\n Enter the allocation matrix \n     ");
    for (i=0; i<m; i++)
        printf(" %c",(i+97));
    printf("\n");
    for (i=0; i <n; i++)
    {
        P[i]=i;
        printf("P[%d]  ",P[i]);
        for (j=0; j<m; j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    for (i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            avail[j]-=alloc[i][j];
        }
    }
    printf("\nEnter the MAX matrix \n     ");
    for (i=0; i<m; i++)
    {
        printf(" %c",(i+97));
    }
    printf("\n");
    for (i=0; i <n; i++)
    {
        printf("P[%d]  ",i);
        for (j=0; j<m; j++)
            scanf("%d", &max[i][j]);
    }
    printf("enter the available resources\n");
    for (i=0; i<m; i++)
    {
        printf("%c= ",(i+97));
        scanf("%d",&avail[i]);
    }
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            printf("The following system is not safe");
            break;
        }
    }
    if (flag == 1)
    {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d", ans[n - 1]);
    }
    return (0);
}

