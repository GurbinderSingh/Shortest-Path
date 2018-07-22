#include "ReadWrite_Functions.h"
#define MAX_STR 25

int matrixSize = 0;

void showMenu()
{
    printf("================= MENU ==================\n"
           "1: Read graph from console input.\n"
           "2: Read graph from file.\n"
           "3: Print graph to console.\n"
           "4: Print graph to file.\n"
           "5: Find shortest path.\n"
           "6: Edit DOT-file settings.\n"
           "7: Export graph as DOT-file.\n"
           "0: EXIT.\n"
           "=========================================\n");
}

char **getNodesfromUser()
{
    int nrNodes = 0, i = 0;
    char **tmp = NULL, buffer[11] = "";

    printf("\n================================ "
           "Enter Nodes "
           "=================================\n");

    do
    {
        printf("Number of nodes: ");
        scanf(" %s", buffer);

        nrNodes = atoi(buffer);
    } while (nrNodes < 0 || nrNodes >= (INF - NOT_ALLOWED_NODES));

    tmp = calloc(nrNodes + 1, sizeof(char *));

    if (NULL == tmp)
    {
        printf("Memory full!\n");
        return tmp;
    }
    tmp[nrNodes] = NULL;

    printf("\n");

    for (i = 0; i < nrNodes; i++)
    {
        tmp[i] = calloc(MAX_STR, sizeof(char));

        if (NULL == tmp[i])
        {
            printf("Memory full\n");
            for (i--; i >= 0; i--)
            {
                free(tmp[i]);
            }
            return tmp;
        }
        printf("%d. Node: ", i + 1);
        scanf(" %s", tmp[i]);
    }
    return tmp;
}

struct edge *getGraphfromUser(char **nodes)
{
    struct edge *tmpHead = NULL, *tmp = NULL;
    int i = 0, index = 1;

    if (nodes == NULL)
        return NULL;

    tmpHead = calloc(1, sizeof(struct edge));

    if (NULL == tmpHead)
    {
        printf("Memory full!");
        return tmp;
    }

    printf("\n=============================== "
           "Enter graph "
           "=================================\n");

    for (i = 0; nodes[i] != NULL; i++)
        printf("For Node [%s] : %d\n", nodes[i], i + 1);

    printf("===============================\n");

    if (i == 0)
        return NULL;

    printf("\n>>> ZERO to exit<<<\n\n");

    for (tmp = tmpHead; 1; tmp = tmp->next)
    {
        printf("From Node (index no.): ");
        scanf(" %d", &index);

        if (index < 1)
        {
            tmp->cost = INF;
            tmp->next = NULL;
            return tmpHead;
        }
        tmp->fromNode = index - 1;
        printf("From Node (index no.): ");
        scanf(" %d", &index);

        if (index < 1)
        {
            tmp->cost = INF;
            tmp->next = NULL;
            return tmpHead;
        }
        tmp->toNode = index - 1;
        printf("               Weight: ");
        scanf(" %lf", &(tmp->cost));
        printf("\n");

        tmp->next = calloc(1, sizeof(struct edge));

        if (NULL == tmp)
        {
            printf("Memory full!");
            return tmpHead;
        }
    }
    return tmpHead;
}

struct CompleteGraphs *getGraphfromFile()
{
    FILE *readFile = NULL;
    int nrNodes = 0, i = 0;
    char **tmpNodes = NULL, nodeBuffer[MAX_STR] = "", FileName[41] = "";
    int toNodeBuffer = -1, fromNodeBuffer = -1;
    double costBuffer = INF;
    struct edge *tmpGraphHead = NULL;

    struct CompleteGraphs *tmpGraph = NULL;

    tmpGraph = calloc(1, sizeof(struct CompleteGraphs));

    if (tmpGraph == NULL)
        return NULL;

    printf("=========================== "
           "READ GRAPH FROM FILE"
           "============================\n\n"
           "Enter path to file: ");
    scanf(" %40s", FileName);

    readFile = fopen(FileName, "r");

    if (FileName == NULL)
    {
        printf("Error while reading the file.\n");
        perror("Error code: ");
        exit(-1);
    }
    fscanf(readFile, "%d", &nrNodes);
    tmpNodes = calloc(nrNodes + 1, sizeof(char *));

    if (tmpNodes == NULL)
    {
        printf("Memory full!\n");
        return NULL;
    }
    tmpNodes[nrNodes] = NULL;

    tmpGraph->nodes = tmpNodes;

    for (i = 0; i < nrNodes; i++)
    {
        tmpNodes[i] = calloc(MAX_STR, sizeof(char));

        if (tmpNodes[i] == NULL)
        {
            printf("Memory full!\n");

            for (i--; i >= 0; i--)
            {
                free(tmpNodes[i]);
            }
            return NULL;
        }
    }

    for (i = 0; i < nrNodes; i++)
    {
        fscanf(readFile, " %s", nodeBuffer);
        strcpy(tmpNodes[i], nodeBuffer);
    }

    tmpGraphHead = calloc(1, sizeof(struct edge));

    if (tmpGraphHead == NULL)
        return NULL;

    tmpGraph->graphListHead = tmpGraphHead;

    while (fscanf(readFile, "%d %d %lf", &fromNodeBuffer, &toNodeBuffer, &costBuffer) != EOF)
    {
        tmpGraphHead->fromNode = fromNodeBuffer;
        tmpGraphHead->toNode = toNodeBuffer;
        tmpGraphHead->cost = costBuffer;

        tmpGraphHead->next = calloc(1, sizeof(struct edge));
        tmpGraphHead = tmpGraphHead->next;
    }

    tmpGraphHead->cost = INF;
    tmpGraphHead->next = NULL;

    fclose(readFile);
    printf("\n\n================= "
           "EXIT READING "
           "=================\n\n"
           "\n>>> Press any key to exit <<<\n\n");
    scanf(" %s", nodeBuffer);

    return tmpGraph;
}

double **makeMatrix(struct edge *head, char **nodes)
{
    double **tmpMatrix = NULL;
    int i = 0, j = 0, n = 0;
    struct edge *tmp = NULL;

    if (nodes == NULL || head == NULL)
        return NULL;

    for (n = 0; nodes[n] != NULL; n++)
        ;
    matrixSize = n;

    tmpMatrix = calloc(n + 1, sizeof(double *));

    if (NULL == tmpMatrix)
        return NULL;

    for (j = 0; j < n; j++)
    {
        tmpMatrix[j] = calloc(n, sizeof(double));

        if (NULL == tmpMatrix[j])
            return NULL;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            tmpMatrix[i][j] = INF;
        }
    }

    for (tmp = head; tmp != NULL; tmp = tmp->next)
    {
        tmpMatrix[tmp->fromNode][tmp->toNode] = tmp->cost;
    }
    return tmpMatrix;
}

void printGraph(double **matrix)
{
    int i = 0, j = 0;

    printf("=============================== "
           "PRINT MATRIX "
           "=================================\n\n");

    for (i = 0; i < matrixSize; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            if (matrix[i][j] == INF)
            {
                printf("  INF  ");
            }
            else if (matrix[i][j] > 0)
                printf("%5.1f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void writeGraphInFile(struct CompleteGraphs *graph)
{
    FILE *writeFile = NULL;
    char **tmpNodes = NULL, writeFileName[40] = "";
    struct edge *tmp = NULL;
    int i = 0;

    printf("File path: ");
    scanf(" %s", writeFileName);

    writeFile = fopen(writeFileName, "w");
    if (writeFile == NULL)
    {
        printf("Error while reading file.\n");
        perror("Error code: ");
        exit(-1);
    }

    tmpNodes = graph->nodes;

    tmp = graph->graphListHead;

    if (tmpNodes == NULL || tmp == NULL)
        return;

    for (i = 0; tmpNodes[i] != NULL; i++)
        ;

    fprintf(writeFile, "%d\n", i);

    for (i = 0; tmpNodes[i] != NULL; i++)
    {
        strcpy(writeFileName, tmpNodes[i]);
        fprintf(writeFile, "%s\n", writeFileName);
    }

    for (tmp = graph->graphListHead; tmp != NULL; tmp = tmp->next)
    {
        if ((tmp->fromNode || tmp->toNode) != 0 && tmp->cost)
            fprintf(writeFile, "%d %d %.1f\n", tmp->fromNode, tmp->toNode, tmp->cost);
    }
    fclose(writeFile);
}

void freeAll(double **matrix, struct CompleteGraphs *graph)
{
    char **tmp = NULL;
    int i = 0;
    struct edge *tmp2 = NULL;

    if (graph != NULL)
    {
        tmp = graph->nodes;

        for (i = 0; tmp[i] != NULL; i++)
            ;

        for (i--; i >= 0; i--)
            free(tmp[i]);

        free(tmp);

        for (tmp2 = graph->graphListHead; tmp2 != NULL; tmp2 = tmp2->next)
        {
            tmp2 = tmp2->next;

            free(graph->graphListHead);

            graph->graphListHead = tmp2;
        }
    }

    if (matrix != NULL)
    {
        for (i = 0; matrix[i] != NULL; i++)
            ;
        for (i--; i >= 0; i--)
            free(matrix[i]);
    }
}
