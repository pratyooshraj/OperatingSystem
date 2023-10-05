#include<stdio.h>
int findLRU(int time[], int n)
{
    int i, min=time[0], pos = 0;
    for(i = 1; i < n; ++i)
        if(time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    return pos;
}
int main(void)
{
    int nf, np, frames[10], pages[30], c=0, time[10], flag1, flag2, i, j, pos, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &nf);
    printf("Enter number of pages: ");
    scanf("%d", &np);
    printf("Enter reference string: ");
    for(i = 0; i < np; ++i) scanf("%d", &pages[i]);
    for(i = 0; i < nf; ++i) frames[i] = -1;
    printf("Ref string\tPage frames");
    for(i = 0; i < np; ++i)
    {
        printf("\n\t%d\t", pages[i]);
        flag1 = flag2 = 0;
        for(j = 0; j < nf; ++j)
            if(frames[j] == pages[i])
            {
                time[j]=++c;
                flag1=flag2=1;
                break;
            }
        if(flag1 == 0)
            for(j = 0; j < nf; ++j)
                if(frames[j] == -1)
                {
                    faults++;
                    frames[j]=pages[i];
                    time[j]=++c;
                    flag2=1;
                    break;
                }
        if(flag2 == 0)
        {
            pos=findLRU(time, nf);
            faults++;
            frames[pos]=pages[i];
            time[pos]=++c;
        }
        for(j=0; j<nf; ++j) printf("%d\t", frames[j]);
    }
    printf("\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n",np-faults);
    fflush(stdin);
    printf("Page fault percentage = %g\n",(faults*100.0)/np);
}
