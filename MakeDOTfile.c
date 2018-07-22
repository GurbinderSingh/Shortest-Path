#include "MakeDOTfile.h"

void writeInDOT(char** nodes, struct edge* graphs, char **color, int *preced, int nrNodes)
{
    FILE *dotFile=NULL;
    char exitFun=0;
    struct edge *tmp=NULL;
    int i=0, j;


    dotFile=fopen("DOT.gv", "w");
    if(dotFile==NULL)
        return;

    fprintf(dotFile, "digraph myGraph\n{\n");

    for(tmp=graphs; tmp!=NULL; tmp = tmp->next)
    {
        if(tmp->fromNode != tmp->toNode)
        {
            if(preced!=NULL)
            {
                for(i = nrNodes-1; i > 0; i = preced[i])
                {
                    j=preced[i];

                    if(nodes[i] == nodes[tmp->toNode] && nodes[j] == nodes[tmp->fromNode])
                    {
                        fprintf(dotFile, "\t%s->%s[color=red, label=\"%.1f\"]\n", nodes[tmp->fromNode], nodes[tmp->toNode], tmp->cost);
                        break;
                    }
                }
                if(i==0)
                {
                    fprintf(dotFile, "\t%s->%s[label=\"%.1f\"]\n", nodes[tmp->fromNode], nodes[tmp->toNode], tmp->cost);
                }
            }
            else
            {
                fprintf(dotFile, "\t%s->%s[label=\"%.1f\"]\n", nodes[tmp->fromNode], nodes[tmp->toNode], tmp->cost);
            }
        }
    }

    if(color!=NULL)
    {
        for(i=0; i<nrNodes; i++)
            fprintf(dotFile, "\t%s[color=%s]\n", nodes[i], color[i]);
    }


    fprintf(dotFile, "\n}\n");

    fclose(dotFile);


    printf("\n\n============================== "
           "EXPORT AS DOT "
           "===============================\n\n"
           ">>> Press any key to exit <<<\n");
    scanf(" %c", &exitFun);
}
