
#include <stdio.h>
#include <stdlib.h>
#include "P4Headers.h"
#include <string.h>

void* checkedMalloc(size_t size)
{
    void* buffer = malloc(size);
    if(buffer == NULL)
    {
        fprintf(stderr,"malloc error");
        exit(1);
    }
    return buffer;
}

struct hashTable* createdTable(int size)
{
    struct hashTable* table = checkedMalloc(sizeof(struct hashTable));
    table->size = size;
    return table;
}
struct opcodeNode* createdOpcodeNode(char* instruction, int opCode, int numArgs)
{
    struct opcodeNode* O = checkedMalloc(sizeof(struct opcodeNode));
    strcpy(O->instruction,instruction);
    O->numbArgs = numArgs;
    O->opcode = opCode;
    
    return O;
}

void insertOpcode(struct hashTable* table,char* instruction, int opCode, int numArgs )
{
    int h = hash(instruction, table->size);
    
    struct opcodeNode *temp = createdOpcodeNode(instruction,opCode,numArgs);
    temp->next = table->oNodeArray[h];
    table->oNodeArray[h] = temp;

}
int getOpcode(struct hashTable* table,char* instruction)
{
    int h = hash(instruction, table->size);
    
    if(table->oNodeArray[h] != NULL)
    {
        struct opcodeNode* temp = table->oNodeArray[h];
        while(temp != NULL)
        {
         if(strcmp(instruction,temp->instruction) == 0)
         {
             return temp->opcode;
         }
            temp = temp->next;
        }
        return -1;
}
}
int opcodeExist(struct hashTable* table, char* instruction)
{
    int h = hash(instruction,table->size);
    
    if(table->oNodeArray[h] != NULL)
    {
        struct opcodeNode* temp = table->oNodeArray[h];
        while(temp != NULL)
        {
            if(strcmp(instruction,temp->instruction) == 0)
            {
                return 1;
            }
            temp = temp-> next;
        }
        return 0;
    }
}
int getNumArgs(struct hashTable* table,char* instruction)
    {
        int h = hash(instruction, table->size);
        
        if(table->oNodeArray[h] != NULL)
        {
            struct opcodeNode* temp = table->oNodeArray[h];
            while(temp != NULL)
            {
                if(strcmp(instruction,temp->instruction) == 0)
                {
                    return temp->numbArgs;
                }
                temp = temp->next;
            }
 
    }
    }

struct symbolNode* createdSymbolNode(char* symbol, int LC)
{
    struct symbolNode* S = checkedMalloc(sizeof(struct symbolNode));
    strcpy(S->symbol,symbol);
    
    S->LC = LC;
    
    return S;
}
void insertSymbol(struct hashTable* table,char* symbol, int LC)
{
    int h = hash(symbol, table->size);
    
    struct symbolNode* temp = createdSymbolNode(symbol,LC);
    
    temp->next = table->sNodeArray[h];
    table->sNodeArray[h] = temp;
    return -1;

}
    
    
char* getSymbol(struct hashTable* table,char* symbol)
{
    int h = hash(symbol, table->size);
    
    if(table->sNodeArray[h] != NULL)
    {
        struct symbolNode* temp = table->sNodeArray[h];
        while(temp != NULL)
        {
            if(strcmp(symbol,temp->symbol) == 0)
            {
                return temp->LC;
            }
            temp = temp->next;
        }
        return "-1";
    }
}

int symbolExist(struct hashTable* table,char* symbol)
{
    int h = hash(symbol,table->size);

    if(table->sNodeArray[h] != NULL)
    {
        struct symbolNode* temp = table->oNodeArray[h];
        while(temp != NULL)
        {
            if(strcmp(symbol,temp->symbol) == 0)
            {
                return 1;
            }
            temp = temp-> next;
        }
            return 0;
    }
}

struct hashTable* buildOpcodeTable()
{
    struct hashTable* opTable = createdTable(TABLE_SIZE);
    insertOpcode(opTable,"hlt",0,0);
    insertOpcode(opTable,"add",1,3);
    insertOpcode(opTable,"sub",2,3);
    insertOpcode(opTable,"mul",3,3);
    insertOpcode(opTable,"div",4,3);
    insertOpcode(opTable,"mod",5,3);
    insertOpcode(opTable,"move",6,2);
    insertOpcode(opTable,"and",7,3);
    insertOpcode(opTable,"or",8,3);
    insertOpcode(opTable,"xor",9,3);
    insertOpcode(opTable,"com",10,2);
    insertOpcode(opTable,"sll",11,3);
    insertOpcode(opTable,"srl",12,3);
    insertOpcode(opTable,"sra",13,3);
    insertOpcode(opTable,"jr",14,1);
    insertOpcode(opTable,"rdr",15,1);
    insertOpcode(opTable,"prr",16,1);
    insertOpcode(opTable,"prh",17,1);
    insertOpcode(opTable,"li",18,2);
    insertOpcode(opTable,"addi",19,3);
    insertOpcode(opTable,"subi",20,3);
    insertOpcode(opTable,"muli",21,3);
    insertOpcode(opTable,"divi",22,3);
    insertOpcode(opTable,"modi",23,3);
    insertOpcode(opTable,"lwb",24,2);
    insertOpcode(opTable,"swb",25,2);
    insertOpcode(opTable,"lwa",26,2);
    insertOpcode(opTable,"swa",27,2);
    insertOpcode(opTable,"j",28,1);
    insertOpcode(opTable,"jal",29,1);
    insertOpcode(opTable,"jeq",30,3);
    insertOpcode(opTable,"jne",31,3);
    insertOpcode(opTable,"jlt",32,3);
    insertOpcode(opTable,"jle",33,3);
    insertOpcode(opTable,"jgt",34,3);
    insertOpcode(opTable,"jge",35,3);
    
    return opTable;
}
    void objectMaker( int binaryNumber,  int address, FILE* obj)
    {
         int hexadecimal = 0;
         int j=1;
         int remainder;
        
        while(binaryNumber!= 0)
        {
            remainder = binaryNumber%10;
            hexadecimal = hexadecimal+remainder*j;
            j = j*2;
            binaryNumber = binaryNumber/10;
            
        }
        
        fprintf(obj,"%X %X",hexadecimal,address);
    }

