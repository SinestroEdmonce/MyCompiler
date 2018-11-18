#include "Semantic.h"

/* Record the type of return value of a given function */
static Type* func_ret_type;

/* A method for semantic analysis */
void Semantic_Analysis(){
    DFS(root);
}

/* A deepth-first traversal method */
void DFS(TreeNode* cur_root){
    assert(cur_root != NULL); 
    
    if (strcmp(cur_root->type, "ExtDef") == 0){
        DFS_Extern_Defined(cur_root);
    }
    else if (strcmp(cur_root->type, "CompSt") == 0){
        DFS_Compst(cur_root);
    }
    else if (strcmp(cur_root->type, "Exp") == 0){
        DFS_Expression(cur_root);
    }
    else if (strcmp(cur_root->type, "Stmt") == 0){
        DFS_Stmt(cur_root);
    }
    else{
        TreeNode* child = NULL;
        for (child = cur_root->child; child!=NULL; child=child->sibling)
            DFS(child);
    }
}

char* DFS_Id(TreeNode* cur_root) {
    assert(strcmp(cur_root->type, "ID") == 0);
    return cur_root->value;
}

int DFS_Int(TreeNode* cur_root) {
    assert(strcmp(cur_root->type, "INT") == 0);
    return cur_root->value_as_its_type.int_value;
}

float DFS_Float(TreeNode* cur_root) {
    assert(strcmp(cur_root->type, "FLOAT") == 0);
    return cur_root->value_as_its_type.double_value;
}

/* Obtain the var/struct/func name */
char* DFS_Opt_Tag(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "OptTag") == 0);
    return DFS_Id(CHILD(cur_root, 1));
}

/* Obtain the var/struct/func name */
char* DFS_Tag(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "Tag") == 0);
    return DFS_Id(CHILD(cur_root, 1));
}

/* TODO */
bool Is_Type_Equal(const Type* type1_id, const Type* type2_id){

}

/* Deepth-first traversal TODO */
Type* DFS_Expression(TreeNode* cur_root){

}

/* Deepth-first traversal TODO */
Type* DFS_Var_Declared(TreeNode* cur_root, char **symbol_id, Type* type_id){


}

/* Obtain the declared variables' information */
FieldList* DFS_Declared(TreeNode* cur_root, Type* type_id){
    assert(strcmp(cur_root->type, "Dec") == 0);

    FieldList* pt = malloc(sizeof(FieldList));
    pt->field_type = DFS_Var_Declared(CHILD(cur_root, 1), &pt->field_name, type_id);
    pt->next = NULL;

    if (func_ret_type == NULL){
        if (CHILD(cur_root, 3) != NULL)
            Report_Errors(15, cur_root);
    } 
    else if (CHILD(cur_root, 3) != NULL){
        Type* exp_type_id = DFS_Expression(CHILD(cur_root, 3));

        if (Is_Type_Equal(exp_type_id, pt->field_type) == false)
            Report_Errors(5, cur_root);
    }
    if (Insert_Var_Symbol(pt->field_name, pt->field_type) == false){
        if (func_ret_type == NULL)
            Report_Errors(15, cur_root->child); 
        else
            Report_Errors(3, cur_root->child);

        free(pt);
        return NULL;
    }
    return pt;
}

/* Obtain the declared variables' information */
FieldList* DFS_Declared_List(TreeNode* cur_root, Type* type_id){
    assert(strcmp(cur_root->type, "DecList") == 0);

    FieldList* pt = DFS_Declared(CHILD(cur_root, 1), type_id);
    if (CHILD(cur_root, 3) != NULL) {
        if (pt != NULL) 
            pt->next = DFS_Declared_List(CHILD(cur_root, 3), type_id);
        else
            pt = DFS_Declared_List(CHILD(cur_root, 3), type_id);   
    }
    return pt;
}

/* Obtain the field members' information in a given structure */
FieldList* DFS_Defined(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "Def") == 0);

    Type* type_id = DFS_Specifier(CHILD(cur_root, 1));
    if (type_id == NULL) 
        return NULL;

    return DFS_Declared_List(CHILD(cur_root, 2), type_id);
}

/* Obtain the field members' information in a given structure */
FieldList* DFS_Defined_List(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "DefList") == 0);

    FieldList* pt = DFS_Defined(CHILD(cur_root, 1));
    if (CHILD(cur_root, 2) != NULL) {
        if (pt == NULL) {
            pt = DFS_Defined_List(CHILD(cur_root, 2));
        } 
        else{
            FieldList* prev_node = pt;
            while(prev_node->next != NULL)
                prev_node = prev_node->next;

            prev_node->next = DFS_Defined_List(CHILD(cur_root, 2));
        }
    }
    return pt;
}

/* TODO */
Structure* DFS_Structure_Specifier(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "StructSpecifier") == 0);

    Structure* structure;
    if (strcmp(CHILD(cur_root, 2), "OptTag") == 0){
        // StructSpecifier: STRUCT OptTag LC DefList RC
        structure = malloc(sizeof(Structure));

        if (CHILD(cur_root, 4) != NULL && strcmp(CHILD(cur_root, 4)->type, "DefList") == 0){
            Push_Scope();
            structure->fields = DFS_Defined_List(CHILD(cur_root, 4));
            Pop_Scope();
        }
        else
            structure->fields = NULL;

        char* structure_name = DFS_Opt_Tag(CHILD(cur_root, 2));
        /* If find the same structure name in structure hashtable */
        if (Insert_Structure_Symbol(structure_name, structure) == false)
            Report_Errors(16, CHILD(cur_root, 2));
    }
    else if (strcmp(CHILD(cur_root, 2), "LC") == 0){
        // StructSpecifier: STRUCT LC DefList RC
        structure = malloc(sizeof(Structure));

        if (CHILD(cur_root, 3) != NULL && strcmp(CHILD(cur_root, 4)->type, "DefList") == 0){
            Push_Scope();
            structure->fields = DFS_Defined_List(CHILD(cur_root, 3));
            Pop_Scope();
        }
        else
            structure->fields = NULL;
    }
    else if (strcmp(CHILD(cur_root, 2), "Tag") == 0){
        // StructSpecifier: STRUCT Tag
        char* structure_name = DFS_Tag(CHILD(cur_root, 2));

        StructureSymbol* structure_symbol = Find_Structure_Symbol(structure_name);
        if (structure_symbol != NULL)
            structure = structure_symbol->structure_type;
        else{
            Report_Errors(17, CHILD(cur_root, 2));
            return NULL;
        }
    }

    return structure;
}

/* A deepth-first traversal method for searching the Specifier branch */
Type* DFS_Specifier(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "Specifier") == 0);

    Type* pt;
    if (strcmp(CHILD(cur_root, 1)->type, "TYPE") == 0){
        // Specifier: TYPE
        char* type_name = CHILD(cur_root, 1)->value;
        pt = Create_Type_Basic(type_name);

        if (pt->basic == TYPE_OTHERS)
            return NULL;
    }
    else if (strcmp(CHILD(cur_root, 1)->type, "StructSpecifier") == 0){
        // Specifier: StructSpecifier
        pt = malloc(sizeof(Type));
        pt->kind = STRUCTURE;
        pt->structure = DFS_Structure_Specifier(cur_root->child);

        if (pt->structure == NULL)
            return NULL;
    }
    return pt;
}

/* A deepth-first traversal method for searching the ExtDef branch */
void DFS_Extern_Defined(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "ExtDef") == 0);

    Type* type_id = DFS_Specifier(CHILD(cur_root, 1));
    if (type_id == NULL) 
        return;

    if (strcmp(CHILD(cur_root, 2)->type, "ExtDecList") == 0){
        // ExtDef: Specifier ExtDecList SEMI
        DFS_Extern_Declared_List(CHILD(cur_root, 2), type_id);
    }
    else if (strcmp(CHILD(cur_root, 2)->type, "SEMI") == 0){
        // ExtDef: Specifier SEMI
        // Nothing to do
    }
    else if (strcmp(CHILD(cur_root, 2)->type, "FunDec") == 0){
        // ExtDef: Specifier FunDec CompSt
        // ExtDef: Specifier FunDec SEMI
        func_ret_type = type_id;
        
        /* Enter into a deeper scope */
        Push_Scope();
        if (strcmp(CHILD(cur_root, 3)->type, "Compst") == 0){
            /* If the function is declared and implemented */
            DFS_Func_Declared(CHILD(cur_root, 2), type_id, false);
            DFS_Compst(CHILD(cur_root, 3));
        }
        else{
            /* If the function is declared only */
            DFS_Func_Declared(CHILD(cur_root, 2), type_id, true);
        }
        Pop_Scope();
        
        func_ret_type = NULL;
    }
}