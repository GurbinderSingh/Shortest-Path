#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

int allselected(int *selected, int MAX);

void shortestPath(double **cost, int *preced, double *distance, int MAX);

#endif
