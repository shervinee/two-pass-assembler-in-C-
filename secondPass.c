

#include <stdio.h>
#include <stdlib.h>
#include "P4Headers.h"
#include <string.h>

void secondPass(struct line* head, FILE* errFile, FILE* symFile, FILE* objFile)
{
    int memory[MAX_MEMORY_LOC];
    int op;
    int rs1;
    int rs2;
    int rt;
    int sa;
    int address;
    int immediate;
    int numArgs;
    int i;
    struct hashTable* opTable = buildOpcodeTable();//we first create(copy) our hash table of opcodes
    struct hashTable* symTable = createdTable(TABLE_SIZE);
    
    struct line* current = head;
    while(current != NULL)//building the symbol table
    {
       if(current->hasLabel == 1)
       {
           insertSymbol(symTable,current->label,current->LC);
       }
        current = current->next;
    }
    for(i =0; i<MAX_MEMORY_LOC; i++)//looping throgh the memory array to write the instruction onto the file while we are increamenting the line linkedlist
    {
        if(current->hasInstruction == 1)
        {
            op = getOpcode(opTable, current->instruction);
            numArgs = getNumArgs(opTable,current->instruction);
            if(op<18)//check the different cases of a R-format insturction
            {
              if(numArgs == 0)//case for hlt
                 {
                     objectMaker(memory[i], i , objFile);
                 }
                 else if(numArgs == 2)//case for move and com
                 {
                     memmove(current->operands[0],current->operands[0]+1,strlen(current->operands[0])); //removing the dollar sign
                     memmove(current->operands[1],current->operands[1]+1,strlen(current->operands[1]));
                     rt = atoi(current->operands[0]);
                     rs1 =atoi(current->operands[1]);
                     memory[i] = memory[i] | (op << 26);//for the opcode
                     memory[i] = memory[i] | (rs1 << 21);//for the RS1
                     memory[i] = memory[i] |  (rt<< 11);//for the RT
                     
                     objectMaker(memory[i], i , objFile);
                 }
                else if(numArgs == 1)//case for jr, rdr, prr and prh
                {
                    memmove(current->operands[0],current->operands[0]+1,strlen(current->operands[0]));
                    rt = atoi(current->operands[0]);
                    memory[i] = memory[i] | (op << 26);//for the opcode
                    memory[i] = memory[i] | (rt << 11);//for the RT
                    
                    objectMaker(memory[i], i , objFile);
                }
                else if(strcmp(current->instruction,"sll")== 0 || strcmp(current->instruction,"srl") || strcmp(current->instruction,"sra"))
                   {
                       memmove(current->operands[0],current->operands[0]+1,strlen(current->operands[0])); //removing the dollar sign
                       memmove(current->operands[1],current->operands[1]+1,strlen(current->operands[1]));
                       rt = atoi(current->operands[0]);
                       rs1 =atoi(current->operands[1]);
                       sa = atoi(current->operands[2]);
                       memory[i] = memory[i] | (op << 26);//for the opcode
                       memory[i] = memory[i] | (rs1 << 26);//for the RS1
                       memory[i] = memory[i] | (rt << 11);//for the RT
                       memory[i] = memory[i] | (sa << 6);
                       
                       objectMaker(memory[i], i , objFile);

                   }
              else //case for add, sub, mul, div, mod, and, or and xor
                        {
                            memmove(current->operands[0],current->operands[0]+1,strlen(current->operands[0])); //removing the dollar sign
                            memmove(current->operands[1],current->operands[1]+1,strlen(current->operands[1]));
                            memmove(current->operands[2],current->operands[2]+1,strlen(current->operands[2]));
                            rt = atoi(current->operands[0]);
                            rs1 =atoi(current->operands[1]);
                            rs2=atoi(current->operands[2]);
                            memory[i] = memory[i] | (op << 26);//for the opcode
                            memory[i] = memory[i] | (rs1 << 26);//for the RS1
                            memory[i] = memory[i] | (rs2 << 16);
                            memory[i] = memory[i] | (rt << 11);//for the RT
                            
                            objectMaker(memory[i], i , objFile);
                            
                        }
            }
            if(op> 17 && op< 26)//checking all the possibilites for I-format
            {
                if(numArgs == 3)
                {
                    memmove(current->operands[0],current->operands[0]+1,strlen(current->operands[0])); //removing the dollar sign
                    memmove(current->operands[1],current->operands[1]+1,strlen(current->operands[1]));
                    rt = atoi(current->operands[0]);
                    rs1 =atoi(current->operands[1]);
                    immediate = atoi(current->operands[2]);
                }
                
            }
            if(op>25)
            {
                
            }
        }
        if(ftell(errFile) == 0) //shows that the error file is having no content
        {
            if(getSymbol(symTable,current->label) != -1)//traverse through all the lines of file and get all the symbols and writes them onto the .sym file
            fprintf(symFile,"%s   %d",current->label,current->LC);
        }

               current = current->next;
    }
    
}