

#include <stdio.h>
#include <stdlib.h>
#include "P4Headers.h"
#include <string.h>

struct line* firstPass(FILE* infile,FILE* errFile)
{
    char linebuffer[MAX_LENGTH+1];
    char lineCpy[MAX_LENGTH+1];
    char* delimiter = " ";
    char* token1; //token string
    char* token2; //token string
    char* token3;//token string
    char* wordop;//to record the first operand for a word directive
    char* temp;//to tokenize operands for a given instruction
    int i ;
    int lcTemp;
    int lineNum;
    int operand; //used for increasing the LC value when having a word or resw
    struct hashTable* opTable = buildOpcodeTable();//we first create(copy) our hash table of opcodes
    struct hashTable* symTable = createdTable(TABLE_SIZE);
    struct line* head = checkedMalloc(sizeof(struct line));
    head->lineNumber = 1;
    head->LC = 0;
    
    while(fgets(linebuffer,MAX_LENGTH,infile)!= NULL)
    {
        struct line* newl = checkedMalloc(sizeof(struct line));
        newl->next = NULL;
        
        newl->LC = lcTemp;//copying the previous line LC number
        newl->lineNumber = lineNum;//copying the previous line lineNumber
        
        strcpy(lineCpy,linebuffer);
        token1 = strtok(linebuffer,delimiter);
        if(strlen(token1)== 0)
        {
            newl->isBlankOrComment = 1;
        }
        else if(token1[0] == '#')//checks if the first character in token is "#"
        {
            newl->isBlankOrComment = 1;
        }
        else if(strcmp(token1,".text")==0 || strcmp(token1,".data")==0)
        {
            newl->IsWordOrResw = 1;
        }
        else if(token1[strlen(token1)-1] == ':') //checks if the last character in token is ":"
        {
            newl->hasLabel = 1;
            token1[strlen(token1)-1] == '\0';//removes ":" at the end of symbol
            newl->label = token1;
            if(symbolExist(symTable,token1))//if the symbol already exist.produces the error and prints it into error file
            {
               struct errorNode* e = checkedMalloc(sizeof(struct errorNode));
                e->type = mulitplyDefinedSymbol;
                e->line = newl->lineNumber;
                fprintf(errFile,"ERROR : Multiply defined symbol have been used in the source on line %d",e->line);
                fprintf(errFile,"%s",lineCpy);//copy the error line onto the error flle
            }
            else
            {
                insertSymbol(symTable,token1,newl->LC);//adds the symbol to the table
            }
            
            token2 = strtok(NULL,delimiter);
            
            if(token2 != NULL)
            {
                if(opcodeExist(opTable,token2))
                {
                    newl->hasInstruction = 1;
                    newl->instruction = token2;
                    token3 = strtok(NULL,delimiter);
                    int num = getNumArgs(opTable,token2);//get the disired node to find the numArgs
                    for(i=0; i < num; i++ )
                    {
                        temp = strtok(token3,",");
                        strcpy(newl->operands[i], temp);
                    }
                    newl->LC += 1;
                }
                else
                {
                    struct errorNode* e = checkedMalloc(sizeof(struct errorNode));
                    e->type = illegalOpcode;
                    e->line = newl->lineNumber;
                    fprintf(errFile,"ERROR : illegal opcode have been used on line %d",e->line);
                    fprintf(errFile,"%s",lineCpy);//copy the error line onto the error flle
                }
            }
        }
        else if(strcmp(token1,".word")==0)
        {
            token2 = strtok(NULL,delimiter);
            wordop =strtok(token2,":");
            strcpy(newl->operands[0],wordop);
            token3 = (NULL, ":");
            strcpy(newl->operands[1],token3);
            operand = atoi(token3);//converts token3 String into an integer
            newl->LC += operand;
        }
        else if(strcmp(token1,".resw")==0)
        {
            token2 = strtok(NULL,delimiter);
            strcpy(newl->operands[0],token2);
            operand = atoi(token2);
            newl->LC += operand;
        }
        //since the file got no error if the first token was none of the above we would have a line starting with an instruction
        else if(opcodeExist(opTable,token1))
        {
            newl->hasInstruction = 1;
            newl->instruction = token1;
            token2 = strtok(NULL,delimiter);
            int num = getNumArgs(opTable,token2);//get the disired node to find the numArgs
            for(i=0; i < num; i++ )
            {
                temp = strtok(token2,",");
                newl->operands[i] = temp;
            }
            newl->LC += 1;
        }
        else
        {
            struct errorNode* e = checkedMalloc(sizeof(struct errorNode));
            e->type = illegalOpcode;
            e->line = newl->lineNumber;
            fprintf(errFile,"ERROR : illegal opcode have been used on line %d",e->line);
            fprintf(errFile,"%s",lineCpy);//copy the line onto the error file

        }
        //building the linkedList of lines
        struct line* current= head;
        while(current->next != NULL)
        {
            current= current->next;
        }
        current->next = newl;
        
        lineNum = newl->lineNumber+1;
        lcTemp = newl->LC;
    }
    return head;
}