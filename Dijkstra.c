#include "Dijkstra.h"
#define INF 2147483647


int allselected(int *selected, int MAX)
{
    int i;
    for(i=0; i<MAX; i++)
        if(selected[i]==0)
            return 0;
    return 1;
}



void shortestPath(double **cost, int *preced, double *distance, int MAX)
{
    int *selected;
    double dc,smalldist,newdist;
    int current=0,i,k;

    selected = calloc(MAX, sizeof(int));
    if (selected == NULL)
		return;

    for(i=0; i<MAX; i++)
        distance[i]=INF;

    selected[current]=1;
    distance[0]=0;
    current=0;

    while(!allselected(selected, MAX))
    {
        smalldist=INF;
        dc=distance[current];

        for(i=0; i<MAX; i++)
        {
            if(selected[i]==0)
            {
                newdist=dc+cost[current][i];
                if(newdist<distance[i])
                {
                    distance[i]=newdist;
                    preced[i]=current;
                }
                if(distance[i]<smalldist)
                {
                    smalldist=distance[i];
                    k=i;
                }
            }
        }
        current=k;
        selected[current]=1;
    }

    free(selected);
}





