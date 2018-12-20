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
    Local_Var* local_var;
    int var_offset;
    int arg_offset;
} Frame_Info;

/* Variable designed for decsribing the starck frame */
Frame_Info* frame;

Local_Var* Add_Local_Var(OP_TYPE op_type, int num){
    assert(frame!=NULL);

    Local_Var* lvar = malloc(sizeof(Local_Var));
    lvar->kind = op_type;
    lvar->num = num;
    lvar->offset = frame->var_offset;
    lvar->next = frame->local_var;
    
    frame->local_var = lvar;
    frame->var_offset = frame->var_offset - 4;
    return lvar;
}

Local_Var* Add_Args_Var(OP_TYPE op_type, int num){
    assert(frame!=NULL);

    Local_Var* lvar = malloc(sizeof(Local_Var));
    lvar->kind = op_type;
    lvar->num = num;
    lvar->offset = frame->arg_offset;
    lvar->next = frame->local_var;

    frame->local_var = lvar;
    frame->arg_offset = frame->arg_offset + 4;
    return lvar;
}

static struct local_var *dec_local_var(enum op_type kind, int no, int size) {
    assert(frame != NULL);
    struct local_var *var = new(struct local_var, .kind=kind, .no=no);
    frame->arg_offset += size;
    var->offset = frame->arg_offset - 4;
    var->next = frame->variables;
    frame->variables = var;
    return var;
}

static struct local_var *find_variable(enum op_type kind, int no) {
    assert(frame != NULL);
    for (struct local_var *p = frame->variables; p; p = p->next) {
        if (p->kind == kind && p->no == no) return p;
    }
    return NULL;
}

static int get_offset(enum op_type kind, int no) {
    struct local_var *var = find_variable(kind, no);
    if (var) return var->offset;
    else return -1; // -1 means variable not found
}

static void release_frame() {
    assert(frame != NULL);
    while (frame->variables) {
        struct local_var *t = frame->variables;
        frame->variables = t->next;
        free(t);
    }
    free(frame);
    frame = NULL;
}

static void new_frame() {
    frame = new(struct frame_info, NULL, -8, 4);
}

#endif