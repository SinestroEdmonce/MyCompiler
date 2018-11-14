#include "SymbolTable.h"

/* Details of the hash table definition are listed below 
 * @var_func_hashtable: a hash table just for VARIABLE and FUNCTION
 * @structure_hashtable: a hash table just for STRUCTURE
 * @symbol_scope_stack: a stack to record every variable or etc. in the same scope
 */
SymbolNode* var_func_hashtable[HASHTABLE_LENGTH + 1];
SymbolNode* structure_hashtable[HASHTABLE_LENGTH + 1];
// Note: '+1' is for DECLARED_ONLY
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

bool Insert_Var_Func_Symbol_Node(SymbolRecord* symbol_record){
    /* TODO:
     * find wether the symbol has already been declared and defined in the same scope
     */

    unsigned int loc_index_inserted = Hash_Method_PJW(symbol_record->record_name);
    SymbolNode* symbol_node = malloc(sizeof(SymbolNode));
    symbol_node->var_func_symbol = symbol_record;
    
    /* TODO:
     * 1.insert symbol node into hashtable
     * 2.insert symbol node into stack
     */

    
    return true;
}

/* Insert a variable symbol node */
bool Insert_Var_Symbol(char* var_symbol_id, Type* symbol_type){
    assert(symbol_type->kind != FUNCTION);

    SymbolRecord* var_symbol_record = malloc(sizeof(SymbolRecord));
    var_symbol_record->scope_level = scope_level;
    var_symbol_record->symbol_type = symbol_type;
    strcpy(var_symbol_record, var_symbol_id);

    return Insert_Var_Func_Symbol_Node(var_symbol_record);
}

/* Insert a function symbol node */
bool Insert_Func_Symbol(char* func_symbol_id, Type* symbol_type, TreeNode* tree_node){
    assert(symbol_type->kind == FUNCTION);

    SymbolRecord* func_symbol_record = malloc(sizeof(SymbolRecord));
    func_symbol_record->symbol_type = symbol_type;
    strcpy(func_symbol_record->record_name, func_symbol_id);
    func_symbol_record->tree_node = tree_node;
    
    /* Judge whether the given function is declared-only or not only declared but also implemented */
    if (scope_level == IMPLEMENTED)
        func_symbol_record->scope_level = IMPLEMENTED;
    else
        func_symbol_record->scope_level = DECLARED_ONLY;
    
    return Insert_Var_Func_Symbol_Node(func_symbol_record);
}

/* Insert a structure symbol node */
bool Insert_Structure_Symbol(char* structure_symbol_id, Structure* structure){

}