#ifndef __MIPS_ASMGENERATION_H__
#define __MIPS_ASMGENERATION_H__

#include "IRgeneration.h"

/* The type definition of the registers in MIPS ISA */
typedef enum MIPS_REG_{
    REG_ZERO=0,
    REG_AT,
    REG_V0, REG_V1,
    REG_A0, REG_A1, REG_A2, REG_A3,
    REG_T0, REG_T1, REG_T2, REG_T3, REG_T4, REG_T5, REG_T6, REG_T7,
    REG_S0, REG_S1, REG_S2, REG_S3, REG_S4, REG_S5, REG_S6, REG_S7,
    REG_T8, REG_T9,
    REG_K0, REG_K1,
    REG_GP,
    REG_SP,
    REG_FP,
    REG_RA
} MIPS_REG;

/* Operand type in MIPS ISA */
typedef enum MIPS_OP_TYPE_{
    MIPS_OP_LABEL=0,
    MIPS_OP_REG,
    MIPS_OP_IMM,
    MIPS_OP_ADDR
} MIPS_OP_TYPE;

/* Instruction type in MIPS ISA */
typedef enum MIPS_INSTR_TYPE_ {
    MIPS_LABEL=0, MIPS_LI, MIPS_LA,
    MIPS_MOVE, MIPS_ADD, MIPS_ADDI,
    MIPS_SUB, MIPS_MUL, MIPS_DIV,
    MIPS_MFLO, MIPS_LW, MIPS_SW,
    MIPS_J, MIPS_JAL, MIPS_JR,
    MIPS_BEQ, MIPS_BNE, MIPS_BGT,
    MIPS_BLT, MIPS_BGE, MIPS_BLE
} MIPS_INSTR_TYPE;

typedef struct MIPS_Operand_{
    /* The type of the operand */
    MIPS_OP_TYPE kind;

    union {
        int value;
        char* label;
        struct { 
            // MIPS_OP_ADDR use both
            MIPS_REG reg;   // MIPS_OP_REG use this only
            int offset;
        };
    };
} MIPS_OP;

typedef struct MIPS_INSTR_ {
    MIPS_INSTR_TYPE kind;

    union {
        struct {
            MIPS_OP *op1, *op2, *op3;
        };

        MIPS_OP* operand;
        char* label;
    };

    struct MIPS_INSTR_ *prev, *next;
} MIPS_INSTR;

MIPS_INSTR* asm_list_head;
MIPS_INSTR* asm_list_tail;

MIPS_OP* reg_operand[32];

/* Generate different types of MIPS operands */ 
MIPS_OP* Gen_MIPS_Label_Operand(MIPS_OP_TYPE op_type, char* label_name);
MIPS_OP* Gen_MIPS_Imm_Operand(MIPS_OP_TYPE op_type, int value);
MIPS_OP* Gen_MIPS_Reg_Addr_Operand(MIPS_OP_TYPE op_type, MIPS_REG reg, int offset);

/* Generate different types of MIPS instructions */
MIPS_INSTR* Gen_MIPS_1_Op_Instr(MIPS_INSTR_TYPE instr_type, MIPS_OP* operand);
MIPS_INSTR* Gen_MIPS_1_Label_Instr(MIPS_INSTR_TYPE instr_type, char* label_name);
MIPS_INSTR* Gen_MIPS_3_Op_Instr(MIPS_INSTR_TYPE instr_type, MIPS_OP* op1, MIPS_OP* op2, MIPS_OP* op3);

/* Output the assembly code to the file */
void Print_MIPS_ASM(FILE* file, MIPS_INSTR* instr);

/* Obtain the string type of MIPS operands */
char* MIPS_Operand(MIPS_OP* operand);

/* Translate intermediate representation codes into assembly codes */
void Asm_Translatation(IRCode* ir);

/* Generate the MIPS code for loading variables or immediate number */
void Gen_MIPS_Load(IROperand* operand, MIPS_REG reg);

/* Translate every part in intermediate representation codes as a complete function */
void Asm_Func_Block_Generation(IRCode* ir_head, IRCode* ir_tail);

/* Split the intermediate representation codes into parts, 
 * each of which begins with a function(IR_FUNCTION) 
 */
void Asm_Func_Block_Split(IRCode* ir_head, IRCode* ir_tail);

/* Generate the MIPS instructions and output to files */
void Asm_MIPS_Generation(FILE *file);

/* Link new instruction node to the end of the MIPS_Instr list */
MIPS_INSTR* Add_MIPS_Instr(MIPS_INSTR* instr);

#endif
