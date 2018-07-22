#ifndef READWRITE_FUNCTIONS_H_INCLUDED
#define READWRITE_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 2147483647
#define NOT_ALLOWED_NODES 2147483607


struct edge
{
    int fromNode,
        toNode;
    double cost;

    struct edge *next;
};



struct CompleteGraphs
{
    char **nodes;
    struct edge *graphListHead;
};



void showMenu();
char **getNodesfromUser();
struct edge *getGraphfromUser(char**);
void printGraph(double**);
struct CompleteGraphs *getGraphfromFile();
double **makeMatrix(struct edge*, char**);
void writeGraphInFile(struct CompleteGraphs*);
void freeAll(double**, struct CompleteGraphs*);


#endif
