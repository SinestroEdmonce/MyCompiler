#ifndef __STACKFRAME_H__
#define __STACKFRAME_H__

#include "MIPS_ASMgeneration.h"

/* Data structure for local variables */
typedef struct Local_Var_{
    OP_TYPE kind;
         
    int num;
    /* Offset in stack frame related to $fp */
    int offset;
    struct Local_Var_* next;
} Local_Var;

/* Data structure for stack frame */
typedef struct Frame_Info_{
    Local_Var* variable;
    /* Variable offset is assigned with -8 */
    int var_offset;
    /* Arguments offset is assigned with 4 */
    int arg_offset;
} Frame_Info;

/* Variable designed for decsribing the starck frame */
Frame_Info* frame;

Local_Var* Add_Local_Var(OP_TYPE op_type, int num){
    assert(frame != NULL);

    Local_Var* lvar = malloc(sizeof(Local_Var));
    lvar->kind = op_type;
    lvar->num = num;
    lvar->offset = frame->var_offset;
    lvar->next = frame->variable;
    
    frame->variable = lvar;
    frame->var_offset = frame->var_offset - 4;
    return lvar;
}

Local_Var* Add_Args_Var(OP_TYPE op_type, int num){
    assert(frame != NULL);

    Local_Var* lvar = malloc(sizeof(Local_Var));
    lvar->kind = op_type;
    lvar->num = num;
    lvar->offset = frame->arg_offset;
    lvar->next = frame->variable;

    frame->variable = lvar;
    frame->arg_offset = frame->arg_offset+4;
    return lvar;
}

Local_Var* Dec_Local_Var(OP_TYPE op_type, int num, int size){
    assert(frame != NULL && size%4 == 0);

    Local_Var* lvar = malloc(sizeof(Local_Var));
    lvar->kind = op_type;
    lvar->num = num;
    lvar->offset = frame->var_offset;
    lvar->next = frame->variable;

    frame->var_offset = frame->var_offset-size;
    frame->variable = lvar;
    return lvar;
}

Local_Var* Find_Variable(OP_TYPE kind, int num){
    assert(frame!=NULL);

    for(Local_Var* pt=frame->variable;pt!=NULL;pt=pt->next){
        if (pt->kind==kind && pt->num==num)
            return pt;
    }
    return NULL;
}

int Get_Var_Offset(OP_TYPE kind, int num){
    Local_Var* var = Find_Variable(kind, num);
    if (var!=NULL)
        return var->offset;
    else
        return -1;  // The variable has not been found
}

void Release_Frame(){
    assert(frame!=NULL);
    
    while(frame->variable!=NULL){
        Local_Var* temp = frame->variable;
        frame->variable = temp->next;
        free(temp);
    }
    free(frame);
    frame = NULL;
}

void New_Stack_Frame(){
    frame = malloc(sizeof(Frame_Info));
    frame->arg_offset = 4;
    frame->var_offset = -8;
    frame->variable = NULL;
}

#endif