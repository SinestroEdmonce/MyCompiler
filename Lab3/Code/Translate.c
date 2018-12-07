#include "Translate.h"

/* Record the type of return value of a given function */
Type* func_ret_type4translate;

/* A method for semantic analysis */
void Translate_Analysis(){
    Initialize_READ_WRITE();
    Translate_DFS(root);
}

/* A deepth-first traversal method */
void Translate_DFS(TreeNode* cur_root){
    assert(cur_root != NULL); 
    
    if (strcmp(cur_root->type, "ExtDef") == 0){
        Translate_DFS_Extern_Defined(cur_root);
    }
    else if (strcmp(cur_root->type, "CompSt") == 0){
        Translate_DFS_CompSt(cur_root);
    }
    else if (strcmp(cur_root->type, "Exp") == 0){
        Translate_DFS_Expression(cur_root, NULL);
    }
    else if (strcmp(cur_root->type, "Stmt") == 0){
        Translate_DFS_Stmt(cur_root);
    }
    else{
        TreeNode* child = NULL;
        for (child = cur_root->child; child!=NULL; child=child->sibling)
            Translate_DFS(child);
    }
}

char* Translate_DFS_Id(TreeNode* cur_root) {
    assert(strcmp(cur_root->type, "ID") == 0);
    return cur_root->value;
}

int Translate_DFS_Int(TreeNode* cur_root) {
    assert(strcmp(cur_root->type, "INT") == 0);
    return cur_root->value_as_its_type.int_value;
}

float Translate_DFS_Float(TreeNode* cur_root) {
    assert(strcmp(cur_root->type, "FLOAT") == 0);
    return cur_root->value_as_its_type.double_value;
}

/* Obtain the var/struct/func name */
char* Translate_DFS_Opt_Tag(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "OptTag") == 0);
    return Translate_DFS_Id(CHILD(cur_root, 1));
}

/* Obtain the var/struct/func name */
char* Translate_DFS_Tag(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "Tag") == 0);
    return Translate_DFS_Id(CHILD(cur_root, 1));
}

/* Judge whethe two types are structure-equal to each other */
bool Translate_Is_Type_Equal(Type* const type1_id, Type* const type2_id){
    if (type1_id == NULL || type2_id == NULL)
        return false;

    if (type1_id->kind != type2_id->kind)
        return false;
    
    switch(type1_id->kind){
        case BASIC:{
            return (type1_id->basic == type2_id->basic)?true:false;
        }
        case ARRAY:{
            if (Translate_Is_Type_Equal(type1_id->array.elem, type2_id->array.elem) == false)
                return false;
            
            ArraySizeList* type1_id_array = type1_id->array.array_size;
            ArraySizeList* type2_id_array = type2_id->array.array_size;

            while(type1_id_array != NULL && type2_id_array != NULL){
                /* Compare the size of every dimension */
                if (type1_id_array->size != type2_id_array->size)
                    return false;
                
                type1_id_array = type1_id_array->next;
                type2_id_array = type2_id_array->next;
            }
            if (type1_id_array != NULL || type2_id_array != NULL)
                return false;

            return true;
        }
        case STRUCTURE:{
            if (type1_id->structure == type2_id->structure)
                return true;
            
            FieldList* type1_id_field = type1_id->structure->fields;
            FieldList* type2_id_field = type2_id->structure->fields;

            while(type1_id_field != NULL && type2_id_field != NULL){
                if (Translate_Is_Type_Equal(type1_id_field->field_type, type2_id_field->field_type) == false)
                    return false;
                
                type1_id_field = type1_id_field->next;
                type2_id_field = type2_id_field->next;
            }
            if (type1_id_field != NULL || type2_id_field != NULL)
                return false;

            return true;
        }
        case FUNCTION:{
            return false;
        }
        case UNKNOWN:{
            return (strcmp(type1_id->unknown, type2_id->unknown) == 0)?true:false;
        }
        default:{
            return false;
        }
    }
    return false;
}

bool Translate_Is_Params_Args_Equal(FuncParamList* const param, FuncArgsList* const args) {
    FuncParamList* pa = param;
    FuncArgsList* ar = args;

    while(pa!=NULL && ar!=NULL){
        if (Translate_Is_Type_Equal(pa->param_type, ar->args_type) == false)
            return false;
        pa=pa->next;
        ar=ar->next;
    }
    if (pa != NULL || ar != NULL)
        return false;
    
    return true;
}

FieldList* Translate_Get_Field_List(FieldList* head_node, char* field_name) {
    FieldList* pt = head_node;
    while(pt != NULL){
        if (strcmp(pt->field_name, field_name) == 0)
            return pt;
        pt = pt->next;
    }
    return NULL;
}

Type* Translate_Get_Field_Type(Structure* strcuture_type, char* field_name){
    FieldList* structure_field = Translate_Get_Field_List(strcuture_type->fields, field_name);
    if (structure_field == NULL)
        return NULL;
    
    return structure_field->field_type;
}

/* The function that help allocate the declared type's memory size */
int Get_Type_Size(Type* type){
    assert(type->kind != FUNCTION);
    int memory_size = 0;

    switch(type->kind){
        case STRUCTURE:{
            FieldList* field = type->structure->fields;
            while(field!=NULL){
                memory_size += Get_Type_Size(field->field_type);
                field = field->next;
            }
            break;
        }
        case BASIC:{
            /* TODO: Float available */
            memory_size = 4;
            break;
        }
        case ARRAY:{
            memory_size = Get_Type_Size(type->array.elem);
            ArraySizeList* size_list = type->array.array_size;
            
            while(size_list!=NULL){
                memory_size = memory_size*(size_list->size);
                size_list = size_list->next;
            }
            break;
        }
        default: assert(false);
    }
    return memory_size;
}

/* A deepth-first traversal for the Args branch */
FuncArgsList* Translate_DFS_Args(TreeNode* cur_root){
    //Args: Exp COMMA Args|Exp
    assert(strcmp(cur_root->type, "Args") == 0);
    
    FuncArgsList* args_list = malloc(sizeof(FuncArgsList));
    IROperand* temp = New_Temp_Var();

    args_list->args_type = Translate_DFS_Expression(CHILD(cur_root, 1), temp);
    args_list->next = NULL;
    args_list->prev = NULL;

    temp = Clean_IR_Temp_Var(temp);
    args_list->operand = temp;

    if (CHILD(cur_root, 3) != NULL){
        args_list->next = Translate_DFS_Args(CHILD(cur_root, 3));
        if (args_list->next != NULL)
            args_list->next->prev = args_list;
    }
    else 
        args_list->next = NULL;

    return args_list;
}

/* Obtain the RELOP type from the expression */
RELOP_TYPE Get_Relop(TreeNode* tree_node, bool flag){
    asssert(strcmp(tree_node->type, "RELOP") == 0);

    if (flag == true){
        if (strcmp(tree_node->value, "==") == 0)
            return RELOP_EQ;
        if (strcmp(tree_node->value, "!=") == 0)
            return RELOP_NEQ;
        if (strcmp(tree_node->value, ">=") == 0)
            return RELOP_GE;
        if (strcmp(tree_node->value, "<=") == 0)
            return RELOP_LE;
        if (strcmp(tree_node->value, "<") == 0)
            return RELOP_L;
        if (strcmp(tree_node->value, ">") == 0)
            return RELOP_G;
    }
    else{
        if (strcmp(tree_node->value, "==") == 0)
            return RELOP_NEQ;
        if (strcmp(tree_node->value, "!=") == 0)
            return RELOP_EQ;
        if (strcmp(tree_node->value, ">=") == 0)
            return RELOP_LE;
        if (strcmp(tree_node->value, "<=") == 0)
            return RELOP_GE;
        if (strcmp(tree_node->value, "<") == 0)
            return RELOP_G;
        if (strcmp(tree_node->value, ">") == 0)
            return RELOP_L;
    }
}

/* A deepth-first traversal for the Exp branch, only aiming at LEFT_VALUE branch */
Type* Translate_DFS_Expression_Address(TreeNode* cur_root, IROperand* operand){
    assert(strcmp(cur_root->type, "Exp") == 0);

}

/* A deepth-first traversal for the Exp branch, only aiming at CONDITION branch */
Type* Translate_DFS_Expression_Condition(TreeNode* cur_root, IROperand* label_true, IROperand* label_false){
    assert(strcmp(cur_root->type, "Exp") == 0);
    
    if (CHILD(cur_root, 3)!=NULL && strcmp(CHILD(cur_root, 1)->type, "RELOP") == 0){
        IROperand* t1 = New_Temp_Var();
        IROperand* t2 = New_Temp_Var();

        Type* expr1 = Translate_DFS_Expression(CHILD(cur_root, 1), t1);
        t1 = Clean_IR_Temp_Var(t1);
        Type* expr2 = Translate_DFS_Expression(CHILD(cur_root, 3), t2);
        t2 = Clean_IR_Temp_Var(t2);

        if (expr1 == NULL || expr2 == NULL)
            return NULL;
        if (label_true != NULL && label_false != NULL){
            Gen_3_Operands_Code(IR_IF_GOTO, label_false, t1, t2, Get_Relop(CHILD(cur_root, 2), true));
            Gen_1_Operands_Code(IR_GOTO, label_false);
        }
        else if (label_true != NULL){
            Gen_3_Operands_Code(IR_IF_GOTO, label_true, t1, t2, Get_Relop(CHILD(cur_root, 2), true));
        }
        else if (label_false != NULL){
            Gen_3_Operands_Code(IR_IF_GOTO, label_false, t1, t2, Get_Relop(CHILD(cur_root, 2), false));
        }
        return expr1;
    }
    else if (CHILD(cur_root, 3)!=NULL && strcmp(CHILD(cur_root, 2)->type, "AND") == 0){
        Type* expr1 = NULL;
        Type* expr2 = NULL;

        if (label_false!=NULL){
            expr1 = Translate_DFS_Expression_Condition(CHILD(cur_root, 1), NULL, label_false);
            expr2 = Translate_DFS_Expression_Condition(CHILD(cur_root, 3), label_true, label_false);
        }
        else{
            IROperand* label1 = New_Label();
            expr1 = Translate_DFS_Expression_Condition(CHILD(cur_root, 1), NULL, label1);
            expr2 = Translate_DFS_Expression_Condition(CHILD(cur_root, 3), label_true, label_false);
            Gen_1_Operands_Code(IR_LABEL, label1);
        }
        if (expr1 == NULL || expr2 == NULL)
            return NULL;
        
        return expr1;
    }
    else if (CHILD(cur_root, 3)!=NULL && strcmp(CHILD(cur_root, 2)->type, "OR") == 0){
        Type* expr1 = NULL;
        Type* expr2 = NULL;

        if (label_true!=NULL){
            expr1 = Translate_DFS_Expression_Condition(CHILD(cur_root, 1), label_true, NULL);
            expr2 = Translate_DFS_Expression_Condition(CHILD(cur_root, 3), label_true, label_false);
        }
        else{
            IROperand* label1 = New_Label();
            expr1 = Translate_DFS_Expression_Condition(CHILD(cur_root, 1), label1, NULL);
            expr2 = Translate_DFS_Expression_Condition(CHILD(cur_root, 3), label_true, label_false);
            Gen_1_Operands_Code(IR_LABEL, label1);
        }
        if (expr1 == NULL || expr2 == NULL)
            return NULL;
        
        return expr1;
    }
    else if (CHILD(cur_root, 3) == NULL && strcmp(CHILD(cur_root, 1)->type, "NOT") == 0){
        Type* exp_type = Translate_DFS_Expression_Condition(CHILD(cur_root, 2), label_false, label_true);

        if (exp_type == NULL) 
            return NULL;
        
        return exp_type;
    }
    else{
        IROperand* t1 = New_Temp_Var();
        Type* exp_type = Translate_DFS_Expression(cur_root, t1);
        t1 = Clean_IR_Temp_Var(t1);
        IROperand* imme_zero = New_Immediate(0);

        if (label_true != NULL & label_false != NULL){
            Gen_3_Operands_Code(IR_IF_GOTO, label_true, t1, &imme_zero, RELOP_NEQ);
            Gen_1_Operands_Code(IR_GOTO, label_false);
        }
        else if (label_false != NULL){
            Gen_3_Operands_Code(IR_IF_GOTO, label_false, t1, &imme_zero, RELOP_EQ);
        }
        else if (label_true != NULL){
            Gen_3_Operands_Code(IR_IF_GOTO, label_true, t1, &imme_zero, RELOP_NEQ);
        }
        return exp_type;
    }
    assert(false);
}

/* A deepth-first traversal for the Exp branch */
Type* Translate_DFS_Expression(TreeNode* cur_root, IROperand* operand){
    assert(strcmp(cur_root->type, "Exp") == 0);

    if (CHILD(cur_root, 2) == NULL){
        // Exp: ID|INT|FLOAT
        if (strcmp(CHILD(cur_root, 1)->type, "ID") == 0){
            char* id_name = Translate_DFS_Id(CHILD(cur_root, 1));
            SymbolRecord* symbol = Find_Var_Func_Symbol(id_name);

            if (symbol == NULL){
                // Report_Errors(1, CHILD(cur_root, 1));
                return NULL;
            }
            return symbol->symbol_type;
        }
        else if (strcmp(CHILD(cur_root, 1)->type, "INT") == 0){
            Translate_DFS_Int(CHILD(cur_root, 1));
            Type* int_type = NULL;
            Create_Type_Basic(&int_type, "int");
            return int_type;
        }
        else{
            Translate_DFS_Float(CHILD(cur_root, 1));
            Type* float_type = NULL;
            Create_Type_Basic(&float_type, "float");
            return float_type;
        }
    }
    else if (CHILD(cur_root, 3) == NULL){
        //Exp: MINUS Exp|NOT Exp
        if (strcmp(CHILD(cur_root, 1)->type, "MINUS") == 0){
            Type* type_exp = Translate_DFS_Expression(CHILD(cur_root, 2));

            if (type_exp == NULL)
                return NULL;
            else if (type_exp->kind == BASIC)
                return type_exp;
            else{
                // Report_Errors(7, CHILD(cur_root, 2));
                return NULL;
            }
        }
        else{
            Type* type_exp = Translate_DFS_Expression(CHILD(cur_root, 2));
            if (type_exp == NULL)
                return NULL;
            if (type_exp->kind == BASIC && type_exp->basic == TYPE_INT)
                return type_exp;
            else{
                // Report_Errors(7, CHILD(cur_root, 2));
                return NULL;
            }
        }
    }
    else if (CHILD(cur_root, 4) == NULL && strcmp(CHILD(cur_root, 2)->type, "LP") != 0) {
        /* Exp: Exp ASSIGNOP Exp|Exp AND Exp
         *     |Exp RELOP Exp|Exp PLUS Exp
         *     |Exp MINUS Exp|Exp STAR Exp
         *     |Exp DIV Exp|LP Exp RP
         *     |Exp OR Exp|Exp DOT ID 
         */
        if (strcmp(CHILD(cur_root, 2)->type, "Exp") == 0)
            return Translate_DFS_Expression(CHILD(cur_root, 2));
        else if (strcmp(CHILD(cur_root, 2)->type, "ASSIGNOP") == 0){
            Type* left_exp_type = Translate_DFS_Expression(CHILD(cur_root, 1));
            Type* right_exp_type = Translate_DFS_Expression(CHILD(cur_root, 3));

            if (left_exp_type == NULL || right_exp_type == NULL)
                return NULL;
            
            TreeNode* left_node = CHILD(cur_root, 1);
            TreeNode* child_depend = left_node;
            int left_value_flag = child_depend->left_value;
            // Find the node that can be treated as a left value
            while(child_depend->left_value == DEPEND_ON_CHILD)
                child_depend = CHILD(child_depend, child_depend->child_num_depend);

            if (child_depend->left_value == ID_LEFT){
                assert(strcmp(child_depend->type, "ID") == 0);

                SymbolRecord* symbol_depend = Find_Var_Func_Symbol(child_depend->value);
                if (symbol_depend != NULL && symbol_depend->symbol_type->kind != FUNCTION)
                    left_value_flag = 1;
            }
            else
                left_value_flag = child_depend->left_value;
            
            if (left_value_flag == NOT_LEFT_VALUE){
                // Report_Errors(6, CHILD(cur_root, 1));
                return NULL;
            }
            if (Translate_Is_Type_Equal(left_exp_type, right_exp_type) == false){
                // Report_Errors(5, cur_root);
                return NULL;
            }
            return left_exp_type;
        }
        else if (strcmp(CHILD(cur_root, 2)->type, "DOT") == 0){
            Type* exp_type = Translate_DFS_Expression(CHILD(cur_root, 1));

            if (exp_type == NULL)
                return NULL;
            
            if (exp_type->kind != STRUCTURE){
                // Report_Errors(13, CHILD(cur_root, 1));
                return NULL;
            }

            Type* field_type = Translate_Get_Field_Type(exp_type->structure, Translate_DFS_Id(CHILD(cur_root, 3)));
            if (field_type != NULL)
                return field_type;
            else{
                // Report_Errors(14, CHILD(cur_root, 3));
                return NULL;
            }
        }
        else{
            Type* left_exp_type = Translate_DFS_Expression(CHILD(cur_root, 1));
            Type* right_exp_type = Translate_DFS_Expression(CHILD(cur_root, 3));
            
            if (left_exp_type == NULL || right_exp_type == NULL)
                return NULL;
            
            if (Translate_Is_Type_Equal(left_exp_type, right_exp_type) == false){
                // Report_Errors(7, cur_root);
                return NULL;
            }

            if (strcmp(CHILD(cur_root, 2)->type, "OR") == 0 || strcmp(CHILD(cur_root, 2)->type, "AND") == 0){
                if (left_exp_type->kind != BASIC){
                    // Report_Errors(7, cur_root);
                    return NULL;
                }
                if (left_exp_type->basic != TYPE_INT){
                    // Report_Errors(7, cur_root);
                    return NULL;
                }
            }
            else{
                if (left_exp_type->kind != BASIC){
                    // Report_Errors(7, cur_root);
                    return NULL;
                }
            }
            return left_exp_type;
        }
    }
    else if (strcmp(CHILD(cur_root, 1)->type, "ID") == 0){
        // Exp: ID LP Args RP|ID LP RP
        SymbolRecord* func_symbol = Find_Var_Func_Symbol(Translate_DFS_Id(CHILD(cur_root, 1)));

        if (func_symbol == NULL){
            // Report_Errors(2, CHILD(cur_root, 1));
            return NULL;
        }

        if (func_symbol->symbol_type->kind != FUNCTION){
            // Report_Errors(11, CHILD(cur_root, 1));
            return NULL;
        }

        FuncArgsList* args_list = NULL;
        if (strcmp(CHILD(cur_root, 3)->type, "Args") == 0)
            args_list = Translate_DFS_Args(CHILD(cur_root, 3));
        
        FuncParamList* param_list = func_symbol->symbol_type->func.param_list;
        if (Translate_Is_Params_Args_Equal(param_list, args_list) == false){
            // Report_Errors(9, CHILD(cur_root, 3));
        }
            
        
        return func_symbol->symbol_type->func.rtn;
    }
    else if (strcmp(CHILD(cur_root, 1)->type, "Exp") == 0){
        // Exp: Exp LB Exp RB
        Type* left_exp_type = Translate_DFS_Expression(CHILD(cur_root, 1));

        Type* pt = NULL;
        if (left_exp_type == NULL || left_exp_type->kind != ARRAY){
            // Report_Errors(10, CHILD(cur_root, 0));
        }
        else{
            pt = malloc(sizeof(Type));
            // Create a copy 
            *pt = *left_exp_type;
            pt->array.array_size = pt->array.array_size->next;
            if (pt->array.array_size == NULL){
                Type* tmp = pt;
                pt = pt->array.elem;
                free(tmp);
            }
        }

        Type* right_exp_type = Translate_DFS_Expression(CHILD(cur_root, 3));
        if (right_exp_type == NULL || right_exp_type->kind != BASIC || right_exp_type->basic != TYPE_INT){
            // Report_Errors(12, CHILD(cur_root, 3));
        }
        return pt;   
    }

    assert(false);
    return NULL;
}

/* Deepth-first traversal for searching the VarDec branch */
Type* Translate_DFS_Var_Declared(TreeNode* cur_root, char **symbol_id, Type* type_id){
    assert(strcmp(cur_root->type, "VarDec") == 0);

    if (strcmp(CHILD(cur_root, 1)->type, "ID") == 0){
        // VarDec: ID
        *symbol_id = Translate_DFS_Id(CHILD(cur_root, 1));
        return type_id;
    }
    
    // VarDec: VarDec LB INT RB
    TreeNode* tree_node = cur_root;
    ArraySizeList* head_node = malloc(sizeof(ArraySizeList));

    head_node->size = CHILD(tree_node, 3)->value_as_its_type.int_value;
    head_node->next = NULL;
    head_node->prev = NULL;

    tree_node = CHILD(tree_node, 1);
    while(strcmp(CHILD(tree_node, 1)->type, "VarDec") == 0) {
        ArraySizeList* next_node =malloc(sizeof(ArraySizeList));
        next_node->size = CHILD(tree_node, 3)->value_as_its_type.int_value;
        next_node->next = head_node;
        next_node->prev = NULL;
        head_node = next_node;
        tree_node = CHILD(tree_node, 1);
    }

    *symbol_id = Translate_DFS_Id(CHILD(tree_node, 1));
    Type* array_type = malloc(sizeof(Type));
    array_type->kind =ARRAY;
    array_type->array.array_size = head_node;
    array_type->array.elem = type_id;

    return array_type;
}

/* Deepth-first traversal for searching the Dec branch */
FieldList* Translate_DFS_Declared(TreeNode* cur_root, Type* type_id){
    assert(strcmp(cur_root->type, "Dec") == 0);

    FieldList* pt = malloc(sizeof(FieldList));
    pt->field_type = Translate_DFS_Var_Declared(CHILD(cur_root, 1), &(pt->field_name), type_id);
    pt->next = NULL;
    pt->prev = NULL;

    Insert_Var_Symbol(pt->field_name, pt->field_type, true);
    if (func_ret_type4translate == NULL){
        // In structure
        return pt;
    }
    else{
        // In function
        if (CHILD(cur_root, 2) == NULL){
            // Dec: VarDec
            if (pt->field_type->kind == STRUCTURE || pt->field_type->kind == ARRAY){
                IROperand* operand = Find_Var_Func_Symbol(pt->field_name)->operand;
                Gen_2_Operands_Code(IR_DEC, NULL, operand, Get_Type_Size(pt->field_type));
            }
        }
        else{
            // Dec: VarDec ASSIGNOP Exp
            /* According to the regulation, only ID can be assigned with a initialized value */
            assert(strcmp(cur_root->child->child->type, "ID") == 0);

            IROperand* operand = Find_Var_Func_Symbol(pt->field_name)->operand;
            Type* exp_type = Translate_DFS_Expression(CHILD(cur_root, 3), operand);
        }
    }
    return pt;
}

/* Deepth-first traversal for searching the DecList branch */
FieldList* Translate_DFS_Declared_List(TreeNode* cur_root, Type* type_id){
    assert(strcmp(cur_root->type, "DecList") == 0);

    FieldList* pt = Translate_DFS_Declared(CHILD(cur_root, 1), type_id);
    if (CHILD(cur_root, 3) != NULL) {
        if (pt != NULL){
            pt->next = Translate_DFS_Declared_List(CHILD(cur_root, 3), type_id);
            if(pt->next != NULL)
                pt->next->prev = pt;
        }
        else
            pt = Translate_DFS_Declared_List(CHILD(cur_root, 3), type_id);   
    }
    return pt;
}

/* Obtain the field members' information in a given structure 
 * Deepth-first traversal for searching the Def branch 
 */
FieldList* Translate_DFS_Defined(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "Def") == 0);

    Type* type_id = Translate_DFS_Specifier(CHILD(cur_root, 1));
    if (type_id == NULL) 
        return NULL;

    return Translate_DFS_Declared_List(CHILD(cur_root, 2), type_id);
}

/* Obtain the field members' information in a given structure 
 * Deepth-first traversal for searching the DefList branch 
 */
FieldList* Translate_DFS_Defined_List(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "DefList") == 0);

    FieldList* pt = Translate_DFS_Defined(CHILD(cur_root, 1));
    if (CHILD(cur_root, 2) != NULL) {
        if (pt == NULL) {
            pt = Translate_DFS_Defined_List(CHILD(cur_root, 2));
        } 
        else{
            FieldList* prev_node = pt;
            while(prev_node->next != NULL)
                prev_node = prev_node->next;

            prev_node->next = Translate_DFS_Defined_List(CHILD(cur_root, 2));
            if (prev_node->next != NULL)
                prev_node->next->prev = prev_node;
        }
    }
    return pt;
}

/* Deepth-first traversal for searching the StructSpecifier branch */
Structure* Translate_DFS_Structure_Specifier(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "StructSpecifier") == 0);

    Structure* structure;
    if (strcmp(CHILD(cur_root, 2)->type, "OptTag") == 0){
        // StructSpecifier: STRUCT OptTag LC DefList RC
        structure = malloc(sizeof(Structure));

        if (CHILD(cur_root, 4) != NULL && strcmp(CHILD(cur_root, 4)->type, "DefList") == 0){
            Push_Scope();
            structure->fields = Translate_DFS_Defined_List(CHILD(cur_root, 4));
            Pop_Scope();
        }
        else
            structure->fields = NULL;

        char* structure_name = Translate_DFS_Opt_Tag(CHILD(cur_root, 2));
        /* Never find the same structure name in structure hashtable, if the semantic check is already done */
        Insert_Structure_Symbol(structure_name, structure);
    }
    else if (strcmp(CHILD(cur_root, 2)->type, "LC") == 0){
        // StructSpecifier: STRUCT LC DefList RC
        structure = malloc(sizeof(Structure));

        if (CHILD(cur_root, 3) != NULL && strcmp(CHILD(cur_root, 3)->type, "DefList") == 0){
            Push_Scope();
            structure->fields = Translate_DFS_Defined_List(CHILD(cur_root, 3));
            Pop_Scope();
        }
        else
            structure->fields = NULL;
    }
    else if (strcmp(CHILD(cur_root, 2)->type, "Tag") == 0){
        // StructSpecifier: STRUCT Tag
        char* structure_name = Translate_DFS_Tag(CHILD(cur_root, 2));

        StructureSymbol* structure_symbol = Find_Structure_Symbol(structure_name);
        if (structure_symbol != NULL)
            structure = structure_symbol->structure_type;
    }

    return structure;
}

/* A deepth-first traversal method for searching the Specifier branch */
Type* Translate_DFS_Specifier(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "Specifier") == 0);

    Type* pt = NULL;
    if (strcmp(CHILD(cur_root, 1)->type, "TYPE") == 0){
        // Specifier: TYPE
        char* type_name = CHILD(cur_root, 1)->value;
        Create_Type_Basic(&pt, type_name);

        if (pt->basic == TYPE_OTHERS)
            return NULL;
    }
    else if (strcmp(CHILD(cur_root, 1)->type, "StructSpecifier") == 0){
        // Specifier: StructSpecifier
        pt = malloc(sizeof(Type));
        pt->kind = STRUCTURE;
        pt->structure = Translate_DFS_Structure_Specifier(cur_root->child);

        if (pt->structure == NULL)
            return NULL;
    }
    return pt;
}

/* A deepth-first traversal method for searching the ExtDecList branch */
void Translate_DFS_Extern_Declared_List(TreeNode* cur_root, Type* type_id){
    assert(strcmp(cur_root->type, "ExtDecList") == 0);

    char* symbol_id;
    Type* var_type = Translate_DFS_Var_Declared(CHILD(cur_root, 1), &symbol_id, type_id);
    Insert_Var_Symbol(symbol_id, var_type, true);
    
    if (CHILD(cur_root, 3) != NULL)
        Translate_DFS_Extern_Declared_List(CHILD(cur_root, 3), type_id);
}

/* Judge whether two parameter lists are as same as each other */
bool Translate_Is_Params_Equal(FuncParamList* const new, FuncParamList* const old){
    FuncParamList* tmp_new = new;
    FuncParamList* tmp_old = old;

    while(tmp_old != NULL & tmp_new != NULL){
        if (Translate_Is_Type_Equal(tmp_old->param_type, tmp_new->param_type) == false)
            return false;
        
        tmp_new = tmp_new->next;
        tmp_old = tmp_old->next;
    }
    if (tmp_old != NULL || tmp_new != NULL)
        return false;
    
    return true;
}

/* A deepth-first traversal method for searching the ParamDec branch */
Type* Translate_DFS_Param_Declared(TreeNode* cur_root, char **symbol_id){
    assert(strcmp(cur_root->type, "ParamDec") == 0);

    Type* param_type = Translate_DFS_Specifier(CHILD(cur_root, 1));

    if (param_type == NULL)
        return NULL;
    
    if (CHILD(cur_root, 2) != NULL)
        param_type = Translate_DFS_Var_Declared(CHILD(cur_root, 2), symbol_id, param_type);
    return param_type;
}

/* A deepth-first traversal method for searching the VarList branch */
FuncParamList* Translate_DFS_Var_List(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "VarList") == 0);

    FuncParamList* pt = malloc(sizeof(FuncParamList));
    pt->param_type = Translate_DFS_Param_Declared(CHILD(cur_root, 1), &(pt->param_name));
    pt->next = NULL;
    pt->prev = NULL;

    if (CHILD(cur_root, 3) != NULL){
        pt->next = Translate_DFS_Var_List(CHILD(cur_root, 3));
        if (pt->next != NULL)
            pt->next->prev = pt;
    }
    if (pt->param_type == NULL) {
        FuncParamList* rtn = pt->next;
        free(pt);
        return rtn;
    }
    return pt;
}

/* A deepth-first traversal method for searching the FunDec branch */
void Translate_DFS_Func_Declared(TreeNode* cur_root, Type* rtn, bool declared_only){
    assert(strcmp(cur_root->type, "FunDec") == 0);

    Type* func_type = malloc(sizeof(Type));
    func_type->kind = FUNCTION;
    func_type->func.rtn = rtn;
    func_type->func.param_list = NULL;

    // Obtain the ID of the function
    char* func_id = Translate_DFS_Id(CHILD(cur_root, 1));

    if (strcmp(CHILD(cur_root, 3)->type, "VarList") == 0)
        func_type->func.param_list = Translate_DFS_Var_List(CHILD(cur_root, 3));
    if (declared_only == true){
        Set_Scope_Declared_Only();

        SymbolRecord* var_func_symbol = Find_Var_Func_Symbol(func_id);
        Insert_Func_Symbol(func_id, func_type, cur_root, true);

        Reset_Scope();
    }
    else{
        IROperand* operand_func = Gen_Operand(OP_FUNCTION, OP_MDF_NONE, -1, func_id);
        Gen_1_Operands_Code(IR_FUNCTION, operand_func);

        if (strcmp(CHILD(cur_root, 3)->type, "VarList") == 0){
            FuncParamList* pt = func_type->func.param_list;

            while(pt!=NULL){
                Insert_Var_Symbol(pt->param_name, pt->param_type, true);
                SymbolRecord* var_func_symbol = Find_Var_Func_Symbol(pt->param_name);
                IROperand* operand_param = var_func_symbol->operand;
                Gen_1_Operands_Code(IR_PARAM, operand_param);
                
                // All the array or the structure is called by reference..
                if (var_func_symbol->symbol_type->kind != BASIC && var_func_symbol->symbol_type->kind != UNKNOWN) 
                    var_func_symbol->operand = Modify_Operator(operand_param, OP_MDF_DEREFERENCE);
                pt = pt->next;
            }
        }

        // If the function has been declared before, then remove the old declaration and add the new definition
        SymbolRecord* var_func_symbol = Find_Var_Func_Symbol(func_id);
        if (var_func_symbol != NULL && var_func_symbol->scope_level == DECLARED_ONLY){
            FuncParamList* pt_declared = var_func_symbol->symbol_type->func.param_list;
            FuncParamList* pt_new = func_type->func.param_list;

            Delete_Var_Func_Symbol(func_id);
        }
        Insert_Func_Symbol(func_id, func_type, cur_root, true);
    }
}

/*  A deepth-first traversal method for searching the CompSt branch */
void Translate_DFS_CompSt(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "CompSt") == 0);

    if (CHILD(cur_root, 2) != NULL && strcmp(CHILD(cur_root, 2)->type, "DefList") == 0)
        Translate_DFS_Defined_List(CHILD(cur_root, 2));

    if (CHILD(cur_root, 3) != NULL && strcmp(CHILD(cur_root, 3)->type, "StmtList") == 0)
        Translate_DFS(CHILD(cur_root, 3));
    else if (CHILD(cur_root, 2) != NULL && strcmp(CHILD(cur_root, 2)->type, "StmtList") == 0)
        Translate_DFS(CHILD(cur_root, 2));
}

/* A deepth-first traversal method for searching the Stmt branch */
void Translate_DFS_Stmt(TreeNode* cur_root){
    // Stmt: Exp SEMI|CompSt|RETURN Exp SEMI
    //       IF LP Exp RP Stmt|IF LP Exp RP Stmt ELSE Stmt
    //       WHILE LP Exp RP Stmt 
    assert(strcmp(cur_root->type, "Stmt") == 0);

    if (strcmp(CHILD(cur_root,1)->type, "Exp") == 0){
        Translate_DFS_Expression(CHILD(cur_root, 1), NULL);
        return;
    }
    else if (strcmp(CHILD(cur_root,1)->type, "CompSt") == 0){
        Push_Scope();
        Translate_DFS_CompSt(CHILD(cur_root, 1));
        Pop_Scope();
        return;
    }
    else if (strcmp(CHILD(cur_root,1)->type, "RETURN") == 0){
        IROperand* temp = New_Temp_Var();
        Type* rtn_type = Translate_DFS_Expression(CHILD(cur_root, 1), temp);
        temp = Clean_IR_Temp_Var(temp);

        /* If the return value is a basic type, then immediately generate the new IR code.
         * Otherwise, modify the modifier into the token for fetching address(&).
         */
        if (rtn_type->kind == BASIC)
            Gen_1_Operands_Code(IR_RETURN, temp);
        else
            Gen_1_Operands_Code(IR_RETURN, Modify_Operator(temp, OP_MDF_FETCH_ADDR));
        return;
    }
    else if (strcmp(CHILD(cur_root,1)->type, "IF") == 0){
        IROperand* label1 = New_Label();

        if (CHILD(cur_root, 6) == NULL){
            // Stmt: IF LP Exp RP Stmt
            Translate_DFS_Expression_Condition(CHILD(cur_root, 3), NULL, label1);
            Translate_DFS_Stmt(CHILD(cur_root, 5));
            Gen_1_Operands_Code(IR_LABEL, label1);
        }
        else{
            // Stmt: IF LP EXP RP Stmt ELSE Stmt
            Translate_DFS_Expression_Condition(CHILD(cur_root, 3), NULL, label1);
            Translate_DFS_Stmt(CHILD(cur_root, 5));

            IROperand* label2 = New_Label();
            Gen_1_Operands_Code(IR_GOTO, label2);
            Gen_1_Operands_Code(IR_LABEL, label1);
            Translate_DFS_Stmt(CHILD(cur_root, 7));
            Gen_1_Operands_Code(IR_LABEL, label2);
        }
        return;
    }
    else if (strcmp(CHILD(cur_root,1)->type, "WHILE") == 0){
        IROperand* label1 = New_Label();
        IROperand* label2 = New_Label();

        Gen_1_Operands_Code(IR_LABEL, label1);
        Translate_DFS_Expression_Condition(CHILD(cur_root, 3), NULL, label2);
        Translate_DFS_Stmt(CHILD(cur_root, 5));
        
        Gen_1_Operands_Code(IR_GOTO, label1);
        Gen_1_Operands_Code(IR_LABEL, label2);

        return;
    }
    else
        assert(false);
}

/* A deepth-first traversal method for searching the ExtDef branch */
void Translate_DFS_Extern_Defined(TreeNode* cur_root){
    assert(strcmp(cur_root->type, "ExtDef") == 0);

    Type* type_id = Translate_DFS_Specifier(CHILD(cur_root, 1));
    if (type_id == NULL) 
        return;

    if (strcmp(CHILD(cur_root, 2)->type, "ExtDecList") == 0){
        // ExtDef: Specifier ExtDecList SEMI
        Translate_DFS_Extern_Declared_List(CHILD(cur_root, 2), type_id);
    }
    else if (strcmp(CHILD(cur_root, 2)->type, "SEMI") == 0){
        // ExtDef: Specifier SEMI
        // Nothing to do
    }
    else if (strcmp(CHILD(cur_root, 2)->type, "FunDec") == 0){
        // ExtDef: Specifier FunDec CompSt
        // ExtDef: Specifier FunDec SEMI
        func_ret_type4translate = type_id;
        
        /* Enter into a deeper scope */
        Push_Scope();
        if (strcmp(CHILD(cur_root, 3)->type, "CompSt") == 0){
            /* If the function is declared and implemented */
            Translate_DFS_Func_Declared(CHILD(cur_root, 2), type_id, false);
            Translate_DFS_CompSt(CHILD(cur_root, 3));
        }
        else{
            /* If the function is declared only */
            Translate_DFS_Func_Declared(CHILD(cur_root, 2), type_id, true);
        }
        Pop_Scope();
        
        func_ret_type4translate = NULL;
    }
}
