#ifndef __SYMBOLTABLE_H_
#define __SYMBOLTABLE_H_

#include "SymbolType.h"

typedef struct SymbolNode_ {
    /* Some type (eg. structure, function or basic) 
     * Or a specific structure declaration
     */
    union {
        Type* symbol_type;
        StructureSymbol structure_symbol;
    };
    /* Pointer list for open hashing, in order to solve the conflict*/
    struct SymbolNode_ *node_prev, *node_next;
    /* Pointer stack for variables and etc. in the same scope */
    struct SymbolNode_ *stack_prev, *stack_next;
} SymbolNode;

/* Maximum number of embedded blocks */
#define MAX_SCOPE_NUM 32
/* Used for disgtinguishing global variables (etc.) and local or just-declared one */
#define GLOBAL 0
#define DECLARED (MAX_SCOPE_NUM)
/* Maximum length of a hash table */
#define HASHTABLE_LENGTH 0x3fff

unsigned int Hash_Method_PJW(char* name);


#endif