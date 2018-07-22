#ifndef MAKEDOTFILE_H_INCLUDED
#define MAKEDOTFILE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

/*
struct edge
{
    int fromNode,
        toNode;
    double cost;

    struct edge *next;
};
*/
/*
struct CompleteGraphs
{
    char **nodes;
    struct edge *graphListHead;
};
*/

void writeInDOT(char** nodes, struct edge* graphs, char **color, int *preced, int nrNodes);

#endif
