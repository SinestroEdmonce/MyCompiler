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


unsigned int Hash_Method_PJW(char* name){
    unsigned int val = 0, idx;
    for (; *name; ++name){
        val = (val<<2)+(*name);
        if (idx = val & ~HASHTABLE_LENGTH)
            val = (val^(idx>>12)) & HASHTABLE_LENGTH;
    }
    return val;
}