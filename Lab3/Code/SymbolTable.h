#ifndef __SYMBOLTABLE_H_
#define __SYMBOLTABLE_H_

#include<string.h>
#include<assert.h>
#include "SymbolType.h"
#include "ErrorReport.h"

typedef struct SymbolNode_ {
    /* Some type (eg. structure, function or basic) 
     * Or a specific structure declaration
     */
    union {
        SymbolRecord* var_func_symbol;
        StructureSymbol* structure_symbol;
    };
    /* Pointer list for open hashing, in order to solve the conflict*/
    struct SymbolNode_ *node_prev, *node_next;
    /* Pointer stack for variables and etc. in the same scope */
    struct SymbolNode_ *stack_prev, *stack_next;
} SymbolNode;

/* Maximum number of embedded blocks, supposed to be 32 levels of the most embedded scopes */
#define MAX_SCOPE_NUM 33
/* Used for disgtinguishing global variables (etc.) and local or just-declared one */
#define IMPLEMENTED 0
#define DECLARED_ONLY (MAX_SCOPE_NUM)
/* Maximum length of a hash table */
#define HASHTABLE_LENGTH 0x3fff

/* A Function used to calculate hash value */
unsigned int Hash_Method_PJW(char* name);

/* A Function used to find out symbol nodes */
SymbolRecord* Find_Var_Func_Symbol(char* symbol_id);

/* A Function used to find out structure symbol nodes */
StructureSymbol* Find_Structure_Symbol(char* structure_symbol_id);

/* A Function used to insert a variable symbol node */
bool Insert_Var_Symbol(char* symbol_id, Type* symbol_type);

/* A Function used to insert a function symbol node */
bool Insert_Func_Symbol(char* func_symbol_id, Type* symbol_type, TreeNode* tree_node);

/* A Function used to insert a structure symbol node */
bool Insert_Structure_Symbol(char* structure_symbol_id, Structure* structure);

/* A Function used to delete a symbol node in hashtable */
bool Delete_Node_In_Var_Func_Hashtable(SymbolNode* symbol_node);

/* A Function used to delete a structure symbol node in hashtable */
bool Delete_Node_In_Structure_Hashtable(SymbolNode* symbol_node);

/* A Function used to  delete a symbol node in scope stack list,
 * which simply links all symbol nodes that exist in the same scope together
 */
bool Delete_Node_In_Scopestack_List(SymbolNode* symbol_node);

/* A Function used to delete symbols */ 
bool Delete_Var_Func_Symbol(char* symbol_id);
bool Delete_Structure_Symbol(char* symbol_id);


/* A Function used to record the scope that is only for those declared but not defined functions */
 void Set_Scope_Declared_Only();

/* A Function used to restore the scope level */
void Reset_Scope();

/* A Function used to send the type-18 error */
void Check_Declared_Func();

/* A Function used to store a new scope in the stack */
void Push_Scope();

/* A Function used to pop out a scope in the stack */
void Pop_Scope();

/* A Function used to reset the hashtable, the scopestack and the scope level */
void Reset_All();

#endif