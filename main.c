#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "firstfollow.h"


int main(int argc, char* argv[])
{

    char*temp;

    int i,j,x;

    freopen("test.txt","r",stdin);


    tok=scan();


    temp=getNonTerminals(tok);
    strncpy(nonterminals,temp,MAX_GRAMMAR_LENGTH);
    nonTerminalsLength=strlen(nonterminals);
    //printf("Nonterminals{%s}\n",nonterminals);
    temp=getTerminals(tok);
    strncpy(terminals,temp,MAX_GRAMMAR_LENGTH);
    terminalsLength=strlen(terminals);
    //printf("Terminals{%s}",terminals);
    grammar=copyRHS(tok);

    for ( i = 0; i <nonTerminalsLength; i++ )
    {

        for ( j = 0; grammar[i][j]!=NULL; j++ ) printf( "%c grammar=%s \n",nonterminals[i], grammar[i][j]);
    }

    findFirst();

    return 0;
}
