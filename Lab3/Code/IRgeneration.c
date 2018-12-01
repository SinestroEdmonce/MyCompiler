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
    assert(temp_operand->kind == OP_TEMP_VAR);

    if (ir_list_tail->kind == IR_ASSIGN && ir_list_tail->dst == temp_operand){
        /* TODO */
    }

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
        code->src = optimized_src;
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
    assert(ir_list_tail->kind == IR_ASSIGN && ir_list_tail->prev != NULL);

    /* TODO */
}

char* Operand(IROperand* operand){
    return Get_Operand_Representation(operand);
}

/* Output the intermediate representation code to the file */
void Print_IR_Code(FILE* file, IRCode* code){
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
            fprintf(file, "%s := %s", Operand(code->dst), Operand(code->src));
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
