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

/* A list of intermediate representation code (head&tail)*/
IRCode* ir_list_head;
IRCode* ir_list_tail;

IROperand* New_Temp_Var() {
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_TEMP_VAR;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->var_label_num = temp_var_count;

    /* Move to next unused name */
    temp_var_count += 1;

    return new_operand;
}

IROperand* New_Variable() {
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_VARIABLE;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->var_label_num = variable_count;

    /* Move to next unused name */
    variable_count += 1;

    return new_operand;
}

IROperand* New_Label() {
    /* Initialize and create new instances */
    IROperand* new_operand = malloc(sizeof(IROperand));
    new_operand->kind = OP_LABEL;
    new_operand->modifier = OP_MDF_NONE;
    new_operand->var_label_num = label_count;

    /* Move to next unused name */
    label_count += 1;

    return new_operand;
}

/* Obtain the operand representation */
char* Get_operand_Representation(IROperand* operand) {
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
    if (place == ir_list_head){
        ir_list_head = code;
        code->prev = NULL;
    }
    if (place == ir_list) {
        ir_list = code;
        code->prev = NULL;
    } else {
        if (place->prev) place->prev->next = code;
        code->prev = place->prev;
    }
    code->next = place;
    place->prev = code;
    return code;

}

/* Insert a piece of intermediate representation after the current one */
IRCode* Insert_IR_Code_After(IRCode* place, IRCode* code){
        if (place == ir_list_tail) {
        ir_list_tail = code;
        code->next = NULL;
    } else {
        if (place->next) place->next->prev = code;
        code->next = place->next;
    }
    code->prev = place;
    place->next = code;
    return code;
}



