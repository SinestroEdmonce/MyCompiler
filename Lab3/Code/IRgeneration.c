#include "IRgeneration.h"

/* Counting for temporary variables */
static int temp_var_count = 1;

/* Counting for variables */
static int variable_count = 1;

/* Counting for labels */
static int label_count = 1;

/* Symbols/signs for relop */
const char* RELOP[] = {
    "==", "!=", ">", "<", ">=", "<="
};


IROperand* New_Temp_Var(){
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_TEMP_VAR;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->var_label_num = temp_var_count;

    /* Move to next unused name */
    temp_var_count += 1;

    return new_operand;
}

IROperand* New_Variable(){
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_VARIABLE;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->var_label_num = variable_count;

    /* Move to next unused name */
    variable_count += 1;

    return new_operand;
}

IROperand* New_Label(){
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_LABEL;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->var_label_num = label_count;

    /* Move to next unused name */
    label_count += 1;

    return new_operand;
}

IROperand* New_Immediate(int val_res){
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_IMMEDIATE;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->value_int = val_res;

    return new_operand;
}

/* Obtain the operand representation */
char* Get_Operand_Representation(IROperand* operand){
    char buffer[128];

    /* Obtain the modifier before the operand */
    char* modifier;
    switch(operand->modifier){
        case OP_MDF_FETCH_ADDR:{
            modifier = "&"; 
            break;
            }
        case OP_MDF_DEREFERENCE:{
            modifier = "*";
            break;
        }
        default:{
            modifier = "";
            break;
        }
    }

    /* Obtain the name of the given operand */
    switch(operand->kind){
        case OP_FUNCTION:{
            sprintf(buffer, "%s", operand->var_func_name);
            break;
        }
        case OP_IMMEDIATE:{
            sprintf(buffer, "#%d", operand->value_int);
            break;
        }
        case OP_LABEL:{
            sprintf(buffer, "label%d", operand->var_label_num);
            break;
        }
        case OP_TEMP_VAR:{
            sprintf(buffer, "%st%d", modifier, operand->var_label_num);
            break;
        }
        case OP_VARIABLE:{
            sprintf(buffer, "%sv%d", modifier, operand->var_label_num);
            break;
        }
        default: assert(false);
    }

    /* Allocate the memory to store the char[], otherwise it will be retrieved as soon as the function ends. */
    char* rtn = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
    memset(rtn, '\0', strlen(rtn));
    strcpy(rtn, buffer);

    return rtn;
}

/* Remove a piece of intermediate representation */
IRCode* Remove_IR_Code(IRCode* code){
    if (ir_list_head == NULL)
        return NULL;

    if (code == ir_list_head && code == ir_list_tail){
        ir_list_head = ir_list_tail = NULL;
    }
    else if (code == ir_list_tail){
        ir_list_tail = ir_list_tail->prev;
        ir_list_tail->next = NULL;
    }
    else if (code == ir_list_head){
        ir_list_head = ir_list_head->next;
        ir_list_head->prev = NULL;
    }
    else{
        if (code->next != NULL)
            code->next->prev = code->prev;
        if (code->prev != NULL)
            code->prev->next = code->next;
    }
    code->prev = code->next = NULL;

    return code;
}

/* Insert a piece of intermediate representation before the current one */
IRCode* Insert_IR_Code_Before(IRCode* place, IRCode* code){
    if (place == NULL && place != ir_list_head)
        return NULL;
    else if (place == NULL && place == ir_list_head){
        ir_list_head = code;
        code->prev = NULL;
        code->next = NULL;

        ir_list_tail = ir_list_head;
    }
    else if (place == ir_list_head){
        code->next = ir_list_head;
        code->prev = NULL;

        ir_list_head->prev = code;
        ir_list_head = ir_list_head->prev;
    }
    else{
        if (place->prev != NULL)
            place->prev->next = code;
        code->prev = place->prev;
        code->next = place;
        place->prev = code;
    }
    
    return code;
}

/* Insert a piece of intermediate representation after the current one */
IRCode* Insert_IR_Code_After(IRCode* place, IRCode* code){
    if (place == NULL && place != ir_list_tail)
        return NULL;
    else if (place == NULL && place == ir_list_tail){
        ir_list_tail = code;
        code->prev = NULL;
        code->next = NULL;

        ir_list_head = ir_list_tail;
    }
    else if (place == ir_list_tail){
        code->prev = ir_list_tail;
        code->next = NULL;

        ir_list_tail->next = code;
        ir_list_tail = ir_list_tail->next;
    }
    else{
        if (place->next != NULL)
            place->next->prev = code;
        code->next = place->next;
        code->prev = place;
        place->next = code;
    }
    
    return code;
}

IROperand* Clean_IR_Temp_Var(IROperand* temp_operand){
    // assert(temp_operand->kind == OP_TEMP_VAR);

    // if (ir_list_tail->kind == IR_ASSIGN && ir_list_tail->dst == temp_operand){
    //     /* TODO */
    // }

    return temp_operand;
}

/* Link a new piece of intermediate representation code to the IR_list, with some optimization imposed to the code */
void Add_IR_Code(IRCode* code){
    /* Simple optimized adding IR code */
    IROperand* optimized_src = NULL;

    switch(code->kind){
        case IR_DIV:{
            if (code->src1->kind == OP_IMMEDIATE && code->src2->kind == OP_IMMEDIATE){
                int value_res = code->src1->value_int/code->src2->value_int;
                optimized_src = New_Immediate(value_res);
            }
            else if(code->src2->kind == OP_IMMEDIATE && code->src2->value_int == 1){
                optimized_src = code->src1;
            }
            break;
        }
        case IR_MUL:{
            if (code->src1->kind == OP_IMMEDIATE && code->src2->kind == OP_IMMEDIATE){
                int value_res = code->src1->value_int*code->src2->value_int;
                optimized_src = New_Immediate(value_res);
            }
            else if (code->src1->kind == OP_IMMEDIATE && code->src1->value_int == 1){
                optimized_src = code->src2;
            }
            else if (code->src2->kind == OP_IMMEDIATE && code->src2->value_int == 1){
                optimized_src = code->src1;
            }
            break;
        }
        case IR_ADD:{
            if (code->src1->kind == OP_IMMEDIATE && code->src2->kind == OP_IMMEDIATE){
                int value_res = code->src1->value_int*code->src2->value_int;
                optimized_src = New_Immediate(value_res);
            }
            else if (code->src1->kind == OP_IMMEDIATE && code->src1->value_int == 0){
                optimized_src = code->src2;
            }
            else if (code->src2->kind == OP_IMMEDIATE && code->src2->value_int == 0){
                optimized_src = code->src1;
            }
            break;
        }
        case IR_SUB:{
            if (code->src1->kind == OP_IMMEDIATE && code->src2->kind == OP_IMMEDIATE){
                int value_res = code->src1->value_int-code->src2->value_int;
                optimized_src = New_Immediate(value_res);
            }
            else if (code->src2->kind == OP_IMMEDIATE && code->src2->value_int == 0){
                optimized_src = code->src1;
            }
            break;
        }
        default: break;
    }

    /* TODO:
     * Support given float value...
     */
    
    if (optimized_src != NULL){
        IRCode* tmp = code;
        
        code = malloc(sizeof(IRCode));
        code->kind = IR_ASSIGN;
        code->merged_src = optimized_src;
        code->dst = tmp->dst;
        
        free(tmp);
    }
    
    if (ir_list_head == NULL){
        ir_list_head = ir_list_tail = code;
        code->prev = code->next = NULL;
    }
    else{
        ir_list_tail->next = code;
        code->prev = ir_list_tail;
        ir_list_tail = code;
    }
}

void Clean_IR_Assign(){
    // assert(ir_list_tail->kind == IR_ASSIGN && ir_list_tail->prev != NULL);

    // /* TODO */
}

char* Operand(IROperand* operand){
    return Get_Operand_Representation(operand);
}

/* Output the intermediate representation code to the file */
void Print_IR_Code(FILE* file, IRCode* code){
    if (file != NULL){
        switch(code->kind) {
            case IR_LABEL:{
                fprintf(file, "LABEL %s :", Operand(code->src));
                break;
            }
            case IR_FUNCTION:{
                fprintf(file, "FUNCTION %s :", Operand(code->src));
                break;
            }       
            case IR_ASSIGN:{
                fprintf(file, "%s := %s", Operand(code->dst), Operand(code->merged_src));
                break;
                }
            case IR_ADD:{
                fprintf(file, "%s := %s + %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_SUB:{
                fprintf(file, "%s := %s - %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_MUL:{
                fprintf(file, "%s := %s * %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_DIV:{
                fprintf(file, "%s := %s / %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_GOTO:{
                fprintf(file, "GOTO %s", Operand(code->src));
                break;
            }
            case IR_IF_GOTO:{
                fprintf(file, "IF %s %s %s GOTO %s", Operand(code->src1),RELOP[code->relop], Operand(code->src2), Operand(code->dst));
                break;
            }
            case IR_RETURN:{
                fprintf(file, "RETURN %s", Operand(code->src));
                break;
            }
            case IR_DEC:{
                fprintf(file, "DEC %s %d", Operand(code->src), code->declared_size);
                break;
            }
            case IR_ARG:{
                fprintf(file, "ARG %s", Operand(code->src));
                break;
            }
            case IR_CALL:{
                fprintf(file, "%s := CALL %s", Operand(code->rtn), Operand(code->func));
                break;
            }
            case IR_PARAM:{
                fprintf(file, "PARAM %s", Operand(code->src));
                break;
            }
            case IR_READ:{
                fprintf(file, "READ %s", Operand(code->src));
                break;
            }
            case IR_WRITE:{
                fprintf(file, "WRITE %s", Operand(code->src));
                break;
            }
            default: assert(false);
        }
        fprintf(file, "\n");
    }
    else{
        switch(code->kind) {
            case IR_LABEL:{
                printf("LABEL %s :", Operand(code->src));
                break;
            }
            case IR_FUNCTION:{
                printf("FUNCTION %s :", Operand(code->src));
                break;
            }       
            case IR_ASSIGN:{
                printf("%s := %s", Operand(code->dst), Operand(code->merged_src));
                break;
                }
            case IR_ADD:{
                printf("%s := %s + %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_SUB:{
                printf("%s := %s - %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_MUL:{
                printf("%s := %s * %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_DIV:{
                printf("%s := %s / %s", Operand(code->dst), Operand(code->src1), Operand(code->src2));
                break;
            }
            case IR_GOTO:{
                printf("GOTO %s", Operand(code->src));
                break;
            }
            case IR_IF_GOTO:{
                printf("IF %s %s %s GOTO %s", Operand(code->src1),RELOP[code->relop], Operand(code->src2), Operand(code->dst));
                break;
            }
            case IR_RETURN:{
                printf("RETURN %s", Operand(code->src));
                break;
            }
            case IR_DEC:{
                printf("DEC %s %d", Operand(code->src), code->declared_size);
                break;
            }
            case IR_ARG:{
                printf("ARG %s", Operand(code->src));
                break;
            }
            case IR_CALL:{
                printf("%s := CALL %s", Operand(code->rtn), Operand(code->func));
                break;
            }
            case IR_PARAM:{
                printf("PARAM %s", Operand(code->src));
                break;
            }
            case IR_READ:{
                printf("READ %s", Operand(code->src));
                break;
            }
            case IR_WRITE:{
                printf("WRITE %s", Operand(code->src));
                break;
            }
            default: assert(false);
        }
        printf("\n");
    }
}

/* Output IR_list */
void Print_IR_Code_List(FILE *file){
    if (ir_list_head == NULL)
        return;
    
    IRCode* pt = ir_list_head;
    while(pt!=NULL){
        Print_IR_Code(file, pt);
        pt = pt->next;
    }
}

/* Delete all IRCode* node in IR_list */
void Delete_IR_List(){
    if (ir_list_head == NULL)
        return;
    
    while(ir_list_head!=NULL){
        IRCode* tmp = ir_list_head;
        ir_list_head = ir_list_head->next;
        free(tmp);
    }
    ir_list_head = ir_list_tail = NULL;
}

/* Add new intermediate representation code to IR_list */
void Gen_3_Operands_Code(IR_TYPE ir_type, IROperand* dst, IROperand* src1, IROperand* src2, RELOP_TYPE relop){
    IRCode* new_ir_code = malloc(sizeof(IRCode));
    new_ir_code->kind = ir_type;
    new_ir_code->dst = dst;
    new_ir_code->src1 = src1;
    new_ir_code->src2 = src2;

    switch(ir_type){
        case IR_ADD:case IR_SUB:case IR_MUL:case IR_DIV:{
            new_ir_code->none_flag= false;
            break;
        }
        case IR_IF_GOTO:{
            new_ir_code->relop = relop;
            break;
        }
        default: assert(false);
    }

    if (new_ir_code != NULL)
        Add_IR_Code(new_ir_code);
    else
        assert(false);
}

/* Add new intermediate representation code to IR_list */
void Gen_2_Operands_Code(IR_TYPE ir_type, IROperand* dst, IROperand* src, int size){
    IRCode* new_ir_code = malloc(sizeof(IRCode));
    new_ir_code->kind = ir_type;

    switch(ir_type){
        case IR_DEC:{
            new_ir_code->declared_size = size;
            new_ir_code->src = src;
            break;
        }
        case IR_ASSIGN:{
            new_ir_code->dst = dst;
            new_ir_code->merged_src = src;
            break;
        }
        case IR_CALL:{
            new_ir_code->rtn = dst;
            new_ir_code->func = src;
            break;
        }
        default: assert(false);
    }

    if (new_ir_code != NULL)
        Add_IR_Code(new_ir_code);
    else
        assert(false);
}

/* Add new intermediate representation code to IR_list */
void Gen_1_Operands_Code(IR_TYPE ir_type, IROperand* src){
    IRCode* new_ir_code = malloc(sizeof(IRCode));
    new_ir_code->kind = ir_type;
    new_ir_code->src = src;
    new_ir_code->none_flag = false;
    
    if (new_ir_code != NULL)
        Add_IR_Code(new_ir_code);
    else
        assert(false);
}

/* Generate new immediate operand */
IROperand* Gen_Imme_Op(int value_int, float value_float, bool flag){
    IROperand* new_imme = malloc(sizeof(IROperand));
    new_imme->kind = OP_IMMEDIATE;
    new_imme->modifier = OP_MDF_NONE;

    if (flag==true)
        new_imme->value_int = value_int;
    else
        new_imme->value_float = value_float;

    return new_imme;
}

IROperand* Modify_Operator(IROperand* operand, MODIFIER_TYPE mod_type){
    assert(operand->kind == OP_TEMP_VAR || operand->kind == OP_VARIABLE);

    IROperand* operand_instead = malloc(sizeof(IROperand));
    *operand_instead = *operand;

    switch(operand->modifier){
        case OP_MDF_NONE:{
            operand_instead->modifier = mod_type;
            break;
        }
        case OP_MDF_FETCH_ADDR:{
            assert(mod_type == OP_MDF_DEREFERENCE);
            operand_instead->modifier = OP_MDF_NONE;
            break;
        }
        case OP_MDF_DEREFERENCE:{
            assert(mod_type == OP_MDF_FETCH_ADDR);
            operand_instead->modifier = OP_MDF_NONE;
            break;
        }
        default: assert(false);
    }
    return operand_instead;
}

/* Generate new operands */
IROperand* Gen_Operand(OP_TYPE op_type, MODIFIER_TYPE mod_type, int num, char* name){
    IROperand* new_op = malloc(sizeof(IROperand));
    new_op->kind = op_type;
    new_op->modifier = mod_type;

    switch(op_type){
        case OP_LABEL:case OP_TEMP_VAR:{
            new_op->var_label_num = num;
            break;
        }
        case OP_VARIABLE:case OP_FUNCTION:{
            new_op->var_func_name = name;
            break;
        }
        default: assert(false);
    }

    return new_op;

}

