#ifndef __FIRSTFOLLOW__H__
#define __FIRSTFOLLOW__H__

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAMMAR_LENGTH 500

char *tok;
char *firstSet;//[MAX_GRAMMAR_LENGTH];
char ***grammar;
char nonterminals[MAX_GRAMMAR_LENGTH];
char terminals[MAX_GRAMMAR_LENGTH];
int nonTerminalsLength=0;
int terminalsLength=0;

void initGrammar(void);
char* removeNull(char *s);
char*getTerminals(char*s);
char*getNonTerminals(char*s);
int countProductions(char ch);
char *scan(void);

char* scan(void)
{
    char*tokens;
    char ch;
    int i=0;
    int len;
    tokens=(char*)malloc(MAX_GRAMMAR_LENGTH*sizeof(char));
    for(i=0;i<MAX_GRAMMAR_LENGTH;i++)tokens[i]='0';
    len=-1;
    ch=getchar();
    while(!feof(stdin) || ch!=EOF)
    {
        if(isspace(ch)==0)
        {
            if(tokens[len]=='#' && ch=='#')
            {
                len++;
                tokens[len]=ch;
                break;
            }
            len++;
            tokens[len]=ch;
        }
        ch=getchar();

    }
    len++;
    tokens[len]='\0';
    return tokens;
}
char*removeNull(char*s)
{
    char temp[MAX_GRAMMAR_LENGTH];
    int i=0,j=0;
    for(i=0;i<((int)strlen(s));i++)
    {

        if(s[i]!='0')
        {
            temp[j]=s[i];
            j++;
        }
    }
    temp[j]='\0';
    return temp;
}
char* getNonTerminals(char *tokens)
{
    int i, j, index=0,count=0,len,x;
    char rhs[MAX_GRAMMAR_LENGTH];
    len=(int)strlen(tokens);

    for(i=0;i<len;i++)
    {

        if(tokens[i]=='-')
        {

            rhs[index]=tokens[i-1];
            index++;
        }
    }
    rhs[index]='\0';
    x=(int)strlen(rhs);
    for(i=0;i<x-1;i++)
    {
        if(rhs[i]=='0')continue;

        for(j=i+1;j<x;j++)
        {
            if(rhs[i]==rhs[j])rhs[j]='0';

        }


    }
    for(i=0;i<(int)strlen(rhs);i++)
    {

        if(rhs[i]!='0')count++;
    }

    return removeNull(rhs);
}
char*getTerminals(char *tokens)
{
    int i, j=0,count=0,len;
    char terminals[MAX_GRAMMAR_LENGTH];
    len=(int)strlen(tokens);
    for(i=0;i<(int)strlen(tokens);i++)
    {
        if(islower(tokens[i]))
        {
            terminals[j]=tokens[i];
            j++;
        }
    }
    terminals[j]='\0';
    for(i=0;i<(int)strlen(terminals)-1;i++)
    {
        if(terminals[i]=='0')continue;
        for(j=i+1;j<(int)strlen(terminals);j++)
        {
            if(terminals[i]==terminals[j])terminals[j]='0';
        }

        for(i=0;i<(int)strlen(terminals);i++)
        {
            if(terminals[i]=='0')continue;
            count++;
        }
    }

    return removeNull(terminals);
}
int countProductions(char ch)
{
    int countx=0,i=0;
    for(i=0;i<(int)strlen(tok);i++)
    {
        if(!isupper(tok[i]))
        {
            if(tok[i]=='-' && tok[i-1]==ch)
            {
                countx++;
            }
        }
        else
        {
            continue;
        }

    }
    return countx;
}
char*** copyRHS(char*tokens)
{
    int col,l=0,j,x,k,prodNum,count=0;
    char ***szData;
    char temp[500];

    szData = (char *** )malloc(nonTerminalsLength * sizeof(char ** )) ;

    for(k=0;k<(int)strlen(nonterminals);k++)
    {
        prodNum=countProductions(nonterminals[k]);
        szData[k]=(char**)calloc((prodNum+1),sizeof(char*));
            for(j=0;j<(int)strlen(tokens);j++)
            {

                if(nonterminals[k]==tokens[j] && tokens[j+2]=='>')
                {
                    x=j+3;
                    count=0;
                    col=0;
                    while(tokens[x]!='#')
                    {
                        temp[col]=tokens[x];
                        count++;
                        x++;
                        col++;
                    };
                    temp[col]='#';
                    temp[col+1]='\0';
                    szData[k][l]=(char*)malloc((int)strlen(temp)+1);//250*sizeof(char));

					strncpy(szData[k][l],temp,(int)strlen(temp)+1);
					l=l+1;
                }
            }
			l=0;
        }
    return   szData;
}
int contains(char *s, char ch)
{
	int i,answer;
	for(i=0;i<strlen(s);i++)
	{
		if(s[i]==ch)
		{
			answer=1;
			break;
		}
		else
		{
			answer=0;
		}
	}
	return answer;
}

int hashValue(char ch)
{
    int i, j,k;
    for(i=0;i<strlen(nonterminals);i++)
    {
        if(ch==nonterminals[i])
        break;
    }
    return i;
}
void findFirst(void)
{
    int i, j, k, x, y, m, n, len, fstLen,count=0;
    char***fst;
    fst=(char***)malloc(1*sizeof(char**));
    for(i=0;i<strlen(nonterminals);i++){
        fst[i]=(char**)malloc((strlen(nonterminals))*sizeof(char*));
        fst[0][i]=(char*)malloc((strlen(nonterminals)+strlen(terminals))*sizeof(char));
    }
    for(i=0;i<strlen(nonterminals);i++)
    {
        k=0;
        x=countProductions(nonterminals[i]);
        for(j=0;j<x;j++)
        {
            if(nonterminals[i]==grammar[i][j][0])continue;
            else
            {
                fst[0][i][k]=grammar[i][j][0];
                k++;
            }
        }
        fst[0][i][k]='\0';
        printf("FIRST(%c)={%s}\n",nonterminals[i],fst[0][i]);
    }
    putchar('\n');

    for(i=0;i<strlen(nonterminals);i++)
    {
        for(j=0;j<strlen(fst[0][i]);j++)
        {
            if(isupper(fst[0][i][j]))
            {
                m=hashValue(fst[0][i][j]);
                strcat(fst[0][i],fst[0][m]);
            }
        }
        printf("FIRST(%c)={%s}\n",nonterminals[i],fst[0][i]);
    }
    for(k=0;k<strlen(nonterminals);k++)if(isupper(nonterminals[k]))count++;
}

#endif
