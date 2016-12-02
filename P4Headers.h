
#ifndef P4Headers_h
#define P4Headers_h


#endif /* P4Headers_h */
#define MAX_LENGTH 80
#define MAX_INSTUCTION_L 6
#define MAX_SYMBOL_L 9
#define TABLE_SIZE 70
#define MAX_MEMORY_LOC 65535



struct line {
    int isBlankOrComment ;
    int hasLabel;
    int hasInstruction;
    int lineNumber;
    int LC;
    int IsWordOrResw;
    char* label;
    char* instruction;
    char* operands;
    struct line* next;
};
struct symbolNode{
    //int key;
    int LC;
    char symbol[MAX_SYMBOL_L];
    struct symbolNode* next;
};

struct hashTable{
    int size;
    struct symbolNode** sNodeArray;
    struct opcodeNode** oNodeArray;
};

struct opcodeNode{
    //int key;
    char instruction[MAX_INSTUCTION_L];
    int opcode;
    int numbArgs;
    struct opcodeNode* next;
};

enum errorType{
    undefinedSymbol,
    mulitplyDefinedSymbol,
    illegalOpcode
};

typedef enum errorType errorType;
                
struct errorNode{
    errorType type;
    int line;
    struct errorNode* next;
};
int  hash (char *s,  int T);
void* checkedMalloc(size_t size);
struct hashTable* createdTable(int size);
struct hashTable* buildOpcodeTable();
struct line* firstPass(FILE* infile, FILE* errFile);
void secondPass(struct line* head, FILE* errFile, FILE* symFile, FILE* objFILE);

void insertOpcode(struct hashTable* table,char* instruction, int opCode,int numArgs);
struct opcodeNode* createdOpcodeNode(char* instruction, int opCode,int numArgs);
int getOpcode(struct hashTable* table,char* instruction);
int opcodeExist(struct hashTable* table, char* instruction);
int getNumArgs(struct hashTable* table,char* instruction);

void insertSymbol(struct hashTable* table,char* symbol, int LC);
struct symbolNode* createdSymbolNode(char* symbol, int LC);
char* getSymbol(struct hashTable* table,char* symbol);
int symbolExist(struct hashTable* table,char* symbol);

void objectMaker( int binaryNumber, int address, FILE* obj);


                
