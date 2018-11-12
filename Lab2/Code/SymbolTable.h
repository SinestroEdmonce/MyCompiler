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

/* A Function used to calculate hash value */
unsigned int Hash_Method_PJW(char* name);

/* A Function used to find out symbol nodes */
SymbolNode* Find_Symbol(char* symbol_id);

/* A Function used to find out structure symbol nodes */
StructureSymbol *Find_Structure_Symbol(char* structure_symbol_id);

/* A Function used to insert a symbol node */
bool Insert_Symbol(char* symbol_id, Type* symbol_type);

/* A Function used to insert a function symbol node */
bool Insert_Func_Symbol(char* func_symbol_id, Type* symbol_type, TreeNode* tree_node);

/* A Function used to insert a structure symbol node */
bool Insert_Structure_Symbol(char* structure_symbol_id, Structure* structure);

/* A Function used to store a new scope in the stack */
void Push_Scope();

/* A Function used to pop out a scope in the stack */
void Pop_Scope();

// /* A Function used to TODO */
// void Set_Declared_Scope();

// /* A Function used to TODO */
// void Unset_Declared_Scope();

/* A Function used to delete a symbol node in hashtable */
SymbolNode* Delete_Node_In_Hashtable(SymbolNode* symbol_node);

/* A Function used to  delete a symbol node in scope stack list,
 * which simply links all symbol nodes that exist in the same scope together
 */
SymbolNode* Delete_Node_In_Scopestack_List(SymbolNode* symbol_node);

/* A Function used to delete symbols */ 
bool delete_symbol(char *symbol_id);

// /* A Function used to TODO */
// void Check_Declared_Func();

#endif