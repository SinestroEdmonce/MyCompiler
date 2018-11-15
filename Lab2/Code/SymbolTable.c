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
SymbolRecord* Find_Var_Func_Symbol(char* symbol_id){
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
StructureSymbol* Find_Structure_Symbol(char* structure_symbol_id){
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

/* Look up the hashtable to find out whether there are two same variables or functions in the same scope */
SymbolNode* Find_Node_in_Scope(SymbolRecord* symbol_record, int scope){
    SymbolNode* pt = var_func_hashtable[Hash_Method_PJW(symbol_record->record_name)];

    while(pt != NULL && pt->var_func_symbol->scope_level == scope){
        if (strcmp(pt->var_func_symbol->record_name, symbol_record->record_name) == 0)
            return pt;
        pt=pt->node_next;
    }
    return NULL;
}

/* Insert valid node into the var_func hashtable */
bool Insert_Node_to_Var_Func_Hashtable(SymbolNode* symbol_node){
    /* Locate the node head position */
    unsigned int head_loc_index = Hash_Method_PJW(symbol_node->var_func_symbol->record_name);
    SymbolNode* node_head = var_func_hashtable[head_loc_index];

    if (node_head == NULL){
        node_head = symbol_node;
        node_head->node_prev = NULL;
        node_head->node_next = NULL;
    }
    else{
        /* Locate the inserted node position and insert the node in front of the head */
        SymbolNode* tmp = node_head;
        node_head = symbol_node;
        node_head->node_next = tmp;
        node_head->node_prev = NULL;
        tmp->node_prev = node_head;
    }

    /* Judge whether the node has been successfully inserted */
    if (strcmp(var_func_hashtable[head_loc_index]->var_func_symbol->record_name, symbol_node->var_func_symbol->record_name) == 0)
        return true;
    else
        return false;
}

/* Insert valid node into the stack */
bool Insert_Node_to_Scopestack(SymbolNode* symbol_node, const int scope){
    /* Locate the node head position */
    SymbolNode* node_head = symbol_scope_stack[scope];

    if (node_head == NULL){
        node_head = symbol_node;
        node_head->stack_next = NULL;
        node_head->stack_prev = NULL;
    }
    else{
        /* Locate the inserted node position and insert the node in front of the head */
        SymbolNode* tmp = node_head;
        node_head = symbol_node;
        node_head->stack_next = tmp;
        node_head->stack_prev = NULL;
        tmp->node_prev = node_head;
    }

    /* Judge whether the node has been successfully inserted */
    if (strcmp(symbol_scope_stack[scope]->var_func_symbol->record_name, symbol_node->var_func_symbol->record_name) == 0)
        return true;
    else
        return false;
}

/* Generall inserting method for VARIABLE and FUNCTION */
bool Insert_Var_Func_Symbol_Node(SymbolRecord* symbol_record){
    /* Find wether the symbol has already been declared and defined in the same scope
     */
    if (Find_Node_in_Scope(symbol_record, symbol_record->scope_level) != NULL)
        return false;

    SymbolNode* symbol_node = malloc(sizeof(SymbolNode));
    symbol_node->var_func_symbol = symbol_record;
    
    /* 1.insert symbol node into hashtable
     * 2.insert symbol node into stack
     */
    if (Insert_Node_to_Hashtable(symbol_node) && Insert_Node_to_Scopestack(symbol_node, symbol_node->var_func_symbol->scope_level))
        return true;
    else{
        printf("%s -> %s\n", symbol_record->record_name, "Failed to insert into hashtable");
        return false;
    }
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

/* Insert valid node into the structure hashtable */
bool Insert_Node_to_Structure_Hashtable(SymbolNode* symbol_node){
    /* Locate the head node in structure hashtable */
    unsigned int head_loc_index = Hash_Method_PJW(symbol_node->structure_symbol->structure_name);
    SymbolNode* node_head = structure_hashtable[head_loc_index];

    if (node_head == NULL){
        node_head = symbol_node;
        node_head->node_next = NULL;
        node_head->node_prev = NULL;
    }
    else{
        SymbolNode* temp = node_head;
        node_head = symbol_node;
        node_head->node_next = temp;
        node_head->node_prev = NULL;
        temp->node_prev = node_head;
    }

    if (strcmp(structure_hashtable[head_loc_index]->structure_symbol->structure_name, symbol_node->structure_symbol->structure_name) != 0)
        return false;
    else 
        return true;
}

bool Insert_Structure_Symbol_Node(StructureSymbol* structure_symbol){
    /* Find wether the structure has already been declared and defined in the code
     */
    if(Find_Structure_Symbol(structure_symbol->structure_name) != NULL)
        return false;

    unsigned int loc_index_inserted = Hash_Method_PJW(structure_symbol->structure_name);
    SymbolNode* symbol_node = malloc(sizeof(SymbolNode));
    symbol_node->structure_symbol = structure_symbol;
    
    /* 1.insert structure symbol node into hashtable
     */
    if (Insert_Node_to_Structure_Hashtable(symbol_node))
        return true;
    else{
        printf("%s -> %s\n", structure_symbol->structure_name, "Failed to insert into hashtable");
        return false;
    }
}

/* Insert a structure symbol node */
bool Insert_Structure_Symbol(char* structure_symbol_id, Structure* structure){
    StructureSymbol* structure_symbol = malloc(sizeof(StructureSymbol));
    structure_symbol->structure_type = structure;
    strcpy(structure_symbol->structure_name, structure_symbol_id);

    return Insert_Structure_Symbol_Node(structure_symbol);
}

/* Delete a head node */
bool Delete_Head_Node(SymbolNode** head_node){
    if (*head_node == NULL)
        return true;
    else{
       if ((*head_node)->node_next == NULL){
           free((*head_node));
           (*head_node) = NULL;
           return true;
        }
        else{
            SymbolNode* tmp = (*head_node)->node_next;
            free((*head_node));
            (*head_node) = tmp;
            (*head_node)->node_prev = NULL;
            return true;
        }
    }
}

/* Delete a symbol node in var_func hashtable */
bool Delete_Node_In_Var_Func_Hashtable(SymbolNode* symbol_node){
    unsigned int head_loc_index = Hash_Method_PJW(symbol_node->var_func_symbol->record_name);
    SymbolNode** head_node = &var_func_hashtable[head_loc_index];

    if ((*head_node) == symbol_node){
        return Delete_Head_Node(head_node);
    }
    else{
        SymbolNode* pt = (*head_node);
        while(pt != symbol_node)
            pt = pt->node_next;
        
        /* Reconnect the nodes */
        pt->node_prev->node_next = pt->node_next;
        pt->node_next->node_prev = pt->node_prev;

        free(pt);
        pt = NULL;
    }
}

/* Delete a symbol node in structrue hashtable */
bool Delete_Node_In_Structure_Hashtable(SymbolNode* symbol_node){
    unsigned int head_loc_index = Hash_Method_PJW(symbol_node->structure_symbol->structure_name);
    SymbolNode** head_node = &structure_hashtable[head_loc_index];

    if ((*head_node) == symbol_node){
        return Delete_Head_Node(head_node);
    }
    else{
        SymbolNode* pt = (*head_node);
        while(pt != symbol_node)
            pt = pt->node_next;
        
        /* Reconnect the nodes */
        pt->node_prev->node_next = pt->node_next;
        pt->node_next->node_prev = pt->node_prev;

        free(pt);
        pt = NULL;
        return true;
    }
}

/* Delete a symbol node in scope stack */
bool Delete_Node_In_Scopestack_List(SymbolNode* symbol_node){
    SymbolNode** head_node = &symbol_scope_stack[symbol_node->var_func_symbol->scope_level];

    if ((*head_node) == symbol_node){
        if ((*head_node) == NULL)
            return true;
        
        if ((*head_node)->node_next != NULL){
            SymbolNode* tmp = (*head_node)->node_next;
            free((*head_node));
            (*head_node) = tmp;
            (*head_node)->node_prev = NULL;
            return true;
        }
        else{
            free((*head_node));
            (*head_node) = NULL;
            return true;
        }
    }
    else{
        SymbolNode* pt = (*head_node);
        while(pt != symbol_node)
            pt = pt->node_next;
        
        /* Reconnect the nodes */
        pt->node_prev->node_next = pt->node_next;
        pt->node_next->node_prev = pt->node_prev;

        free(pt);
        pt = NULL;
        return true;
    }
}