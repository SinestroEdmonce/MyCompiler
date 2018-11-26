#ifndef __IRGENERATION_H__
#define __IRGENERATION_H__

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "SyntaxTree.h"

typedef struct IROperand_ {
    enum op_type {
        OP_VARIABLE,
        OP_IMMEDIATE,
        OP_TEMP_VAR,
        OP_LABEL,
        OP_FUNCTION
    } kind;
    enum modifier_type {
        OP_MDF_NONE,
        OP_MDF_AND,
        OP_MDF_STAR
    } modifier;
    union {
        int no;
        int val_int;
        char* name;
    };
} IROperand;

typedef struct IRCode_ {
    enum ir_type {
        IR_LABEL,
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
    union {
        struct {
            IROperand* dst;
            union {
                struct {
                    IROperand* src1;
                    IROperand* src2;
                };
                IROperand* src;
            };
        };
        struct { // 1-operand
            IROperand* op;
        };
        struct { // for RETURN only
            IROperand* ret;
            IROperand* func;
        };
    };
    union {
        enum relop_type {
            RELOP_EQ,
            RELOP_NEQ,
            RELOP_G,
            RELOP_L,
            RELOP_GE,
            RELOP_LE,
        } relop;
        int size;
    };
    struct IRCode_* prev;
    struct IRCode_* next;
} IRCode;

IRCode* ir_list;
IRCode* ir_list_tail;

IRCode* remove_ir_code(IRCode* code);
IRCode* insert_ir_code_before(IRCode* place, IRCode* code);
IRCode* insert_ir_code_after(IRCode* place, IRCode* code);

inline IROperand* new_temp_var();
inline IROperand* new_variable();
inline IROperand* new_label();

char* get_operand_str(IROperand* op);
void add_ir_code(IRCode* code);
void print_ir_code(FILE*, IRCode* code);
void print_ir_list(FILE *fp);
IROperand* ir_clean_temp_var(IROperand* op_temp);
void ir_clean_assign();

#endif