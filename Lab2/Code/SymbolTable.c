#include "SymbolTable.h"

/* Details of the hash table definition are listed below 
 * @var_func_hashtable: a hash table just for VARIABLE and FUNCTION
 * @structure_hashtable: a hash table just for STRUCTURE
 * @symbol_scope_stack: a stack to record every variable or etc. in the same scope
 */
SymbolNode* var_func_hashtable[HASHTABLE_LENGTH + 1];
SymbolNode* structure_hashtable[HASHTABLE_LENGTH + 1];
// Note: '+1' is for DECLARED
SymbolNode* symbol_scope_stack[MAX_SCOPE_NUM + 1]; 
static int scope_level = 0; 

/* Recommended hashing method in the given guidance */
unsigned int Hash_Method_PJW(char* name){
    unsigned int val = 0, idx;
    for (; *name; ++name){
        val = (val<<2)+(*name);
        if (idx = val & ~HASHTABLE_LENGTH)
            val = (val^(idx>>12)) & HASHTABLE_LENGTH;
    }
    return val;
}

/* Look up a specific VARIABLE or FUNCTION symbol */
SymbolNode* Find_Var_Func_Symbol(char* symbol_id){
    /* Obtain hash value */
    unsigned int loc_index = Hash_Method_PJW(symbol_id);

    SymbolNode* pt = var_func_hashtable[loc_index];
    while(pt!=NULL && strcmp(pt->var_func_symbol->record_name, symbol_id)!=0){
        pt=pt->node_next;
    }

    if (pt!=NULL)
        return pt->var_func_symbol;
    else
        return NULL;
}

/* Look up a specific STRUCTURE symbol */
StructureSymbol *Find_Structure_Symbol(char* structure_symbol_id){
    unsigned int loc_index = Hash_Method_PJW(structure_symbol_id);

    SymbolNode* pt = structure_hashtable[loc_index];
    while(pt!=NULL && strcmp(pt->structure_symbol->structure_name, structure_symbol_id)!=0){
        pt=pt->node_next;
    }

    if(pt!=NULL)
        return pt->structure_symbol;
    else
        return NULL;
}

