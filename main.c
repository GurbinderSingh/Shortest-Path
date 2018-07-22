#include "ReadWrite_Functions.h"
#include <MakeDOTfile.h>
#include <Dijkstra.h>

void printThis(char** nodes)
{
    int i=0;

    for(i=0; nodes[i] !=NULL; i++)
        printf("Nodes [ %s ]: %d\n", nodes[i], i+1);
}




int main()
{
    int   i=0, *preced=NULL,  matrixSize=0, changeNode=-1;
    double **matrix=NULL, *distance=NULL;
    char  choice=0, exitChoice=0, **color=NULL;
    struct CompleteGraphs *graph=NULL;



    while('0'!=choice)
    {
        showMenu();
        printf("Choice: ");
        scanf(" %c", &choice);
        printf("\n");

        switch(choice)
        {
        case '1':
        {
            freeAll(matrix, graph);

            graph=calloc(1, sizeof(struct CompleteGraphs));
            if(graph==NULL)
                return -1;

            graph->nodes= getNodesfromUser();
            graph->graphListHead= getGraphfromUser(graph->nodes);
            matrix= makeMatrix(graph->graphListHead, graph->nodes);
            break;
        }


        case '2':
        {
            freeAll(matrix, graph);

            graph=calloc(1, sizeof(struct CompleteGraphs));
            if(graph==NULL)
                return -1;

            graph= getGraphfromFile();
            matrix= makeMatrix(graph->graphListHead, graph->nodes);
            break;
        }


        case '3':
        {
            printGraph(matrix);
            printf("\n========== PRESS ANY KEY THEN ENTER TO EXIT ==========\n");
            scanf(" %c", &exitChoice);
            break;
        }


        case '4':
        {
            writeGraphInFile(graph);
            break;
        }


        case '5':
        {
            printf("\n\n=============================== "
                   "Shortest Path "
                   "=================================\n");

            for(i=0; graph->nodes[i] != NULL; i++);
            matrixSize=i;

            preced=calloc(matrixSize, sizeof(int));
            distance=calloc(matrixSize, sizeof(double));

            shortestPath(matrix, preced, distance, matrixSize);


            printf("Shortest Distance: %.1f\n", distance[matrixSize - 1]);

            printf("Shortest Path: ");
            for (i = matrixSize - 1; i > 0; i = preced[i])
                printf("%s <- ", graph->nodes[i]);

            printf("%s", graph->nodes[0]);


            printf("\n\n========== Press any key to exit ===========\n");
            scanf(" %c", &exitChoice);
            break;
        }


        case '6':
        {
            printThis(graph->nodes);
            printf(">>> Zero to exit <<<\n");

            /*========================================*/
            for(matrixSize=0; graph->nodes[matrixSize] != NULL; matrixSize++);

            color=calloc(matrixSize+1, sizeof(char*));
            if(NULL==color)
                break;

            for(i=0; i<matrixSize; i++)
            {
                color[i]=calloc(10, sizeof(char));

                if(color[i]==NULL)
                {
                    for(i--; i>=0; i--)
                        free(color[i]);

                    break;
                }
                strcpy(color[i], "black");
            }
            /*=======================================*/
            while(1)
            {

                printf("\Choice: ");
                scanf(" %d", &changeNode);
                changeNode--;

                if(changeNode<0)
                    break;

                printf("Color: ");
                scanf(" %9s", color[changeNode]);
            }

            writeInDOT(graph->nodes, graph->graphListHead, color, preced, matrixSize);
            changeNode=-1;
            break;
        }


        case '7':
        {
            writeInDOT(graph->nodes, graph->graphListHead, color, preced, matrixSize);
            break;
        }


        default:
            break;
        }
        system("cls");
    }

    printf("\n=============================== "
           "EXIT PROGRAMM "
           "================================\n\n");
    freeAll(matrix, graph);

    free(preced);
    free(distance);

    if(color!=NULL)
    {
        for(i=0; color[i] != NULL; i++)
            free(color[i]);

        free(color);
    }

    return 0;
}





