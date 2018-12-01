#ifndef __IRGENERATION_H__
#define __IRGENERATION_H__

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include "SyntaxTree.h"

typedef struct IROperand_ {
    /* The type of operands */
    enum OP_TYPE {
        OP_VARIABLE,
        OP_IMMEDIATE,
        OP_TEMP_VAR,
        OP_LABEL,
        OP_FUNCTION
    } kind;

    /* Whether the operand is only a varibale or an address or the dereferenced */
    enum MODIFIER_TYPE {
        OP_MDF_NONE,
        OP_MDF_FETCH_ADDR,
        OP_MDF_DEREFERENCE
    } modifier;

    /* Identify different temporary variables */
    union {
        int var_label_num;
        int value_int;
        float value_float;
        char* var_func_name;
    };

    /* TODO:
     * Distinguish float, int, char*...
     */

} IROperand;

typedef struct IRCode_ {
    /* The type of a piece of intermediate representation */
    enum IR_TYPE {
        IR_LABEL=0,
        IR_FUNCTION,
        IR_ASSIGN,
        IR_ADD,
        IR_SUB,
        IR_MUL,
        IR_DIV,
        IR_GOTO,
        IR_IF_GOTO,
        IR_RETURN,
        IR_DEC,
        IR_ARG,
        IR_CALL,
        IR_PARAM,
        IR_READ,
        IR_WRITE,
    } kind;
    
    /* The places for result and temporary variables */
    union {
        struct {
            IROperand* dst;
            union {
                struct {
                    IROperand* src1;
                    IROperand* src2;
                };
                IROperand* merged_src;
            };
        };

        struct { 
            // 1-operand
            IROperand* src;
        };

        struct { 
            // for RETURN only
            IROperand* rtn;
            IROperand* func;
        };
    };

    /* The type of relop operation */
    union {
        enum RELOP_TYPE {
            RELOP_EQ = 0,
            RELOP_NEQ,
            RELOP_G,
            RELOP_L,
            RELOP_GE,
            RELOP_LE,
        } relop;
        int declared_size;
        bool none_flag;
    };

    /* A bi-direction list */
    struct IRCode_* prev;
    struct IRCode_* next;
} IRCode;


/* A list of intermediate representation code (head&tail)*/
IRCode* ir_list_head;
IRCode* ir_list_tail;

/* Remove a piece of intermediate representation */
IRCode* Remove_IR_Code(IRCode* code);

/* Insert a piece of intermediate representation before the current one */
IRCode* Insert_IR_Code_Before(IRCode* place, IRCode* code);

/* Insert a piece of intermediate representation after the current one */
IRCode* Insert_IR_Code_After(IRCode* place, IRCode* code);

/* Create a new intermediate representation symbol */
IROperand* New_Temp_Var();
IROperand* New_Variable();
IROperand* New_Label();
IROperand* New_Immediate(int val_res);

/* Obtain the operand name and its representation */
char* Get_Operand_Representation(IROperand* operand);

/* Remove some temporary variables */
IROperand* Clean_IR_Temp_Var(IROperand* temp_operand);

/* Remove some unnecessary assignment */
void Clean_IR_Assign();

/* Add new intermediate code */
void Add_IR_Code(IRCode* code);

/* Generate new intemediate code */
void Gen_Code(enum IR_TYPE ir_type, IROperand* dst, IROperand* src1, IROperand* src2, enum RELOP_TYPE relop);

/* Generate new immediate operand */
IROperand* Gen_Imme_Op(int value_int, float value_float, bool flag);

/* Obtain the operand representation */
char* Operand(IROperand* operand);

/* Output the intermediate representation to the file */
void Print_IR_Code(FILE* file, IRCode* code);
void Print_IR_Code_List(FILE *fp);

/* Delete all IRCode* node in IR_list */
void Delete_IR_List();

#endif