#include<string.h>
#include "MIPS_ASMgeneration.h"
#include "StackFrame.h"

static int callee_args_num = 0;

static char buffer[128];

/* Common contents of the header in .asm files */
const char* MIPS_common_header = ".data\n\
_prompt: .asciiz \"Enter an integer:\"\n\
_ret: .asciiz \"\\n\"\n\
.globl main\n\
.text\n\
read:\n\
li $v0, 4\n\
la $a0, _prompt\n\
syscall\n\
li $v0, 5\n\
syscall\n\
jr $ra\n\
\n\
write:\n\
li $v0, 1\n\
syscall\n\
li $v0, 4\n\
la $a0, _ret\n\
syscall\n\
move $v0, $0\n\
jr $ra\n\
\n";

/* MIPS instructions in format of string */
const char* MIPS_instr[] = {
    NULL, "li", "la", "move", "add", "addi", "sub", "mul", "div",
    "mflo", "lw", "sw", "j", "jal", "jr", "beq", "bne", "bgt",
    "blt", "bge", "ble"
};

const char* MIPS_reg_name[] = {
    "$zero",
    "$at",
    "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9",
    "$k0", "$k1",
    "$gp",
    "$sp",
    "$fp",
    "$ra"
};

/* Generate different types of MIPS operands */
MIPS_OP* Gen_MIPS_Label_Operand(MIPS_OP_TYPE op_type, char* label_name){
    assert(op_type == MIPS_OP_LABEL);
    
    MIPS_OP* new_MIPS_op = malloc(sizeof(MIPS_OP));
    new_MIPS_op->kind = op_type;
    new_MIPS_op->label = label_name;

    return new_MIPS_op;
}

MIPS_OP* Gen_MIPS_Imm_Operand(MIPS_OP_TYPE op_type, int value){
    assert(op_type == MIPS_OP_IMM);
    
    MIPS_OP* new_MIPS_op = malloc(sizeof(MIPS_OP));
    new_MIPS_op->kind = op_type;
    new_MIPS_op->value = value;

    return new_MIPS_op;
}

MIPS_OP* Gen_MIPS_Reg_Addr_Operand(MIPS_OP_TYPE op_type, MIPS_REG reg, int offset){
    assert(op_type == MIPS_OP_REG || op_type == MIPS_OP_ADDR);
    
    MIPS_OP* new_MIPS_op = malloc(sizeof(MIPS_OP));
    new_MIPS_op->kind = op_type;
    new_MIPS_op->reg = reg;
    new_MIPS_op->offset = offset;

    return new_MIPS_op;
}

/* Generate different types of MIPS instructions */
MIPS_INSTR* Gen_MIPS_1_Op_Instr(MIPS_INSTR_TYPE instr_type, MIPS_OP* operand){
    MIPS_INSTR* new_MIPS_instr = malloc(sizeof(MIPS_INSTR));
    new_MIPS_instr->kind = instr_type;
    new_MIPS_instr->operand = operand;
    
    return new_MIPS_instr;
}

MIPS_INSTR* Gen_MIPS_1_Label_Instr(MIPS_INSTR_TYPE instr_type, char* label_name){
    MIPS_INSTR* new_MIPS_instr = malloc(sizeof(MIPS_INSTR));
    new_MIPS_instr->kind = instr_type;
    new_MIPS_instr->label = label_name;

    return new_MIPS_instr;
}

MIPS_INSTR* Gen_MIPS_3_Op_Instr(MIPS_INSTR_TYPE instr_type, MIPS_OP* op1, MIPS_OP* op2, MIPS_OP* op3){
    MIPS_INSTR* new_MIPS_instr = malloc(sizeof(MIPS_INSTR));

    new_MIPS_instr->kind = instr_type;
    new_MIPS_instr->op1 = op1;
    new_MIPS_instr->op2 = op2;
    new_MIPS_instr->op3 = op3;

    return new_MIPS_instr;
}

/* Link new instruction node to the end of the MIPS_Instr list */
MIPS_INSTR* Add_MIPS_Instr(MIPS_INSTR* instr){
    if (asm_list_head == NULL){
        instr->next = instr->prev = NULL;
        asm_list_head = asm_list_tail = instr;
    }
    else{
        asm_list_tail->next = instr;
        instr->prev = asm_list_tail;
        asm_list_tail = instr;
    }
    return instr;
}

/* Generate the MIPS instructions and output to files */
void Asm_MIPS_Generation(FILE *file){
    if (file != NULL)
        fprintf(file, "%s", MIPS_common_header);
    else
        printf("%s", MIPS_common_header);

    /* First generate the 0~31 register operands */
    int idx = 0;
    for (;idx<32;++idx){
        reg_operand[idx] = Gen_MIPS_Reg_Addr_Operand(MIPS_OP_REG, (MIPS_REG)idx, -1);
    }

    Asm_Func_Block_Split(ir_list_head, ir_list_tail);
    
    for (MIPS_INSTR* pt = asm_list_head; pt!=asm_list_tail->next; pt=pt->next){
        Print_MIPS_ASM(file, pt);
    }
}

/* Split the intermediate representation codes into parts, each of which begins with a function(IR_FUNCTION) */
void Asm_Func_Block_Split(IRCode* ir_head, IRCode* ir_tail){
    assert(ir_head != NULL && ir_tail != NULL && ir_head != ir_tail);
    
    IRCode* tmp = ir_head->next;
    IRCode* func_block_head = ir_head;

    while(tmp!=ir_tail){
        if (tmp->kind == IR_FUNCTION){
            Asm_Func_Block_Generation(func_block_head, tmp->prev);
            func_block_head = tmp;
        }
        tmp = tmp->next;
    }
    Asm_Func_Block_Generation(func_block_head, ir_tail);
}

/* Translate every part in intermediate representation codes as a complete function */
void Asm_Func_Block_Generation(IRCode* ir_head, IRCode* ir_tail){
    assert(ir_head != NULL && ir_tail != NULL && ir_head != ir_tail);
    assert(ir_head->kind == IR_FUNCTION && frame == NULL);
    
    New_Stack_Frame();

    Add_MIPS_Instr(Gen_MIPS_1_Label_Instr(MIPS_LABEL, ir_head->src->var_func_name));

    /* Generate prologue:
     * sw $fp, 0($sp)
     * sw $ra, -4($sp)
     * move $fp, $sp
     * addi $sp, $sp, -frame_size
     */
    MIPS_INSTR* instr;
    Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_FP], \
        Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
    Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_RA], \
        Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, -4), NULL));
    Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_FP], reg_operand[REG_SP], NULL));
    
    /* frame_size will be back filled later */
    instr = Gen_MIPS_3_Op_Instr(MIPS_ADDI, reg_operand[REG_SP], reg_operand[REG_SP], \
        Gen_MIPS_Imm_Operand(MIPS_OP_IMM, -1));
    Add_MIPS_Instr(instr);
    int* frame_size = &(instr->op3->value);

    /* Put arguments in the stack frame variables table */
    IRCode* pt = ir_head->next;
    while(pt->kind == IR_PARAM){
        Add_Args_Var(pt->src->kind, pt->src->var_label_num);
        pt = pt->next;
    }
    
    /* Process other assembly codes (split them into blocks) */
    while(pt != ir_tail->next){
        switch(pt->kind){
            case IR_FUNCTION: case IR_PARAM: assert(false);
            default:{
                Asm_Translatation(pt);
                break;
            }
        }
        pt = pt->next;
    }

    /* Back fill the frame_size */
    *frame_size = frame->var_offset;
    Release_Frame();
}

/* Generate the MIPS code for loading variables or immediate number */
void Gen_MIPS_Load(IROperand* operand, MIPS_REG reg){
    if (operand->kind == OP_IMMEDIATE){
        Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LI, reg_operand[reg], \
            Gen_MIPS_Imm_Operand(MIPS_OP_IMM, operand->value_int), NULL));
    }
    else if (operand->kind == OP_VARIABLE || operand->kind == OP_TEMP_VAR){
        int offset = Get_Var_Offset(operand->kind, operand->var_label_num);
        if (operand->modifier == OP_MDF_NONE){
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[reg], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_FP, offset), NULL));
        }
        else if (operand->modifier == OP_MDF_FETCH_ADDR){
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LA, reg_operand[reg], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_FP, offset), NULL));
        }
        else if (operand->modifier == OP_MDF_DEREFERENCE){
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[reg], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_FP, offset), NULL));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[reg], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, reg, 0), NULL));
        }
    }
    else
        assert(false);
}

/* Translate intermediate representation codes into assembly codes */
void Asm_Translatation(IRCode* ir){
    /* Special treatment for ir_code: *a=b */
    if (ir->kind == IR_ASSIGN && ir->dst->modifier == OP_MDF_DEREFERENCE){
        int offset = Get_Var_Offset(ir->dst->kind, ir->dst->var_label_num);
        Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[REG_T1], \
            Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_FP, offset), NULL));
        Gen_MIPS_Load(ir->merged_src, REG_T2);
        Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_T2], \
            Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_T1, 0), NULL));
        
        return;
    }

    if (Find_Variable(ir->src->kind, ir->src->var_label_num) == false){
        /* Special treatment for ir_code: DEC v xx */
        if (ir->kind == IR_DEC)
            Dec_Local_Var(ir->src->kind, ir->src->var_label_num, ir->declared_size);
        else
            Add_Local_Var(ir->src->kind, ir->src->var_label_num);
    }

    /* Load dst/src to t1 if needed */
    if (ir->kind == IR_RETURN || ir->kind == IR_ARG || ir->kind == IR_WRITE)
        Gen_MIPS_Load(ir->src, REG_T1);

    /* Load src1 to t2, src2 to t3 if needed */
    if (ir->kind != IR_CALL){
        if (ir->src1 != NULL){
            if (Find_Variable(ir->src1->kind, ir->src1->var_label_num) == false)
                Add_Local_Var(ir->src1->kind, ir->src1->var_label_num);
            Gen_MIPS_Load(ir->src1, REG_T2);  
        }
        if (ir->src2 != NULL){
            if (Find_Variable(ir->src2->kind, ir->src2->var_label_num) == false)
                Add_Local_Var(ir->src2->kind, ir->src2->var_label_num);
            Gen_MIPS_Load(ir->src2, REG_T3);
        }
    }

    /* Translate other intermediate representation code */
    switch (ir->kind){
        case IR_LABEL:{
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "label%d", ir->src->var_label_num);
            Add_MIPS_Instr(Gen_MIPS_1_Label_Instr(MIPS_LABEL, strdup(buffer)));
            break;
        }
        case IR_CALL:{
            Add_MIPS_Instr(Gen_MIPS_1_Op_Instr(MIPS_JAL, \
                Gen_MIPS_Label_Operand(MIPS_OP_LABEL, ir->func->var_func_name)));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_ADDI, reg_operand[REG_SP], \
                reg_operand[REG_SP], Gen_MIPS_Imm_Operand(MIPS_OP_IMM, callee_args_num*4)));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_T1], reg_operand[REG_V0], NULL));
            /* Restore the counter of arguments */
            callee_args_num = 0;
            break;
        }
        case IR_ASSIGN:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_T1], reg_operand[REG_T2], NULL));
            break;
        }
        case IR_ADD:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_ADD, reg_operand[REG_T1], reg_operand[REG_T2], reg_operand[REG_T3]));
            break;
        }
        case IR_SUB:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SUB, reg_operand[REG_T1], reg_operand[REG_T2], reg_operand[REG_T3]));
            break;
        }
        case IR_MUL:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MUL, reg_operand[REG_T1], reg_operand[REG_T2], reg_operand[REG_T3]));
            break;
        }
        case IR_DIV:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_DIV, reg_operand[REG_T2], reg_operand[REG_T3],NULL));
            Add_MIPS_Instr(Gen_MIPS_1_Op_Instr(MIPS_MFLO, reg_operand[REG_T1]));
            break;
        }
        case IR_GOTO:{
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "label%d", ir->src->var_label_num);
            Add_MIPS_Instr(Gen_MIPS_1_Op_Instr(MIPS_J, Gen_MIPS_Label_Operand(MIPS_OP_LABEL, strdup(buffer))));
            break;
        }
        case IR_IF_GOTO:{
            MIPS_INSTR_TYPE branch_type;
            switch (ir->relop){
                case RELOP_EQ:  branch_type = MIPS_BEQ; break;
                case RELOP_NEQ: branch_type = MIPS_BNE; break;
                case RELOP_G:   branch_type = MIPS_BGT; break;
                case RELOP_L:   branch_type = MIPS_BLT; break;
                case RELOP_GE:  branch_type = MIPS_BGE; break;
                case RELOP_LE:  branch_type = MIPS_BLE; break;
            }
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "label%d", ir->dst->var_label_num);
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(branch_type, reg_operand[REG_T2], reg_operand[REG_T3], \
                Gen_MIPS_Label_Operand(MIPS_OP_LABEL, strdup(buffer))));
            break;
        }
        case IR_RETURN:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_V0], reg_operand[REG_T1], NULL));
            /* Generate epilogue:
             * move $sp, $fp
             * lw $ra, -4($sp)
             * lw $fp, 0($sp)
             * jr $ra
             */
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_SP], reg_operand[REG_FP], NULL));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[REG_RA], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, -4), NULL));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[REG_FP], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
            Add_MIPS_Instr(Gen_MIPS_1_Op_Instr(MIPS_JR, reg_operand[REG_RA]));
            break;
        }
        case IR_DEC:
            break;
        case IR_ARG:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_T1], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_ADDI, reg_operand[REG_SP], reg_operand[REG_SP], \
                Gen_MIPS_Imm_Operand(MIPS_OP_IMM, -4)));
            callee_args_num = callee_args_num+1;
            break;
        }
        case IR_READ:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_RA], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
            Add_MIPS_Instr(Gen_MIPS_1_Op_Instr(MIPS_JAL, Gen_MIPS_Label_Operand(MIPS_OP_LABEL, "read")));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_T1], reg_operand[REG_V0], NULL));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[REG_RA], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
            break;
        }
        case IR_WRITE:{
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_RA], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_MOVE, reg_operand[REG_A0], reg_operand[REG_T1], NULL));
            Add_MIPS_Instr(Gen_MIPS_1_Op_Instr(MIPS_JAL, Gen_MIPS_Label_Operand(MIPS_OP_LABEL, "write")));
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_LW, reg_operand[REG_RA], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_SP, 0), NULL));
            break;
        }
        case IR_FUNCTION:
        case IR_PARAM:
            assert(false);
    }

    /* Store the result if required */
    int offset = Get_Var_Offset(ir->src->kind, ir->src->var_label_num);
    /* Store the dst/src into the memory */
    if (ir->kind == IR_ASSIGN || ir->kind == IR_ADD || 
        ir->kind == IR_SUB || ir->kind == IR_DIV || 
        ir->kind == IR_MUL || ir->kind == IR_READ || 
        ir->kind == IR_CALL) {
            Add_MIPS_Instr(Gen_MIPS_3_Op_Instr(MIPS_SW, reg_operand[REG_T1], \
                Gen_MIPS_Reg_Addr_Operand(MIPS_OP_ADDR, REG_FP, offset), NULL));
    }
}

/* Obtain the string type of MIPS operands */
char* MIPS_Operand(MIPS_OP* operand){
    switch (operand->kind){
        case MIPS_OP_ADDR:{
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "%d(%s)", (int)(operand->offset), MIPS_reg_name[operand->reg]);
            return strdup(buffer);
        }
        case MIPS_OP_REG:{
            return MIPS_reg_name[operand->reg];
        }
        case MIPS_OP_LABEL:{
            return operand->label;
        }
        case MIPS_OP_IMM:{
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "%d", operand->value);
            return strdup(buffer);
        }
        default: assert(false);
    }
}

/* Output the .asm result to the files */
void Print_MIPS_ASM(FILE* file, MIPS_INSTR* instr){
    if (file == NULL){
        if (instr->kind == MIPS_LABEL){
            printf("%s:\n", instr->label);
            return;
        }
        printf("%s", MIPS_instr[instr->kind]);
        if (instr->op1 != NULL)
            printf(" %s", MIPS_Operand(instr->op1));
        if (instr->op2 != NULL)
            printf(", %s", MIPS_Operand(instr->op2));
        if (instr->op3 != NULL)
            printf(", %s", MIPS_Operand(instr->op3));
        printf("\n");
    }
    else{
        if (instr->kind == MIPS_LABEL){
            fprintf(file, "%s:\n", instr->label);
            return;
        }
        fprintf(file, "%s", MIPS_instr[instr->kind]);
        if (instr->op1 != NULL)
            fprintf(file, " %s", MIPS_Operand(instr->op1));
        if (instr->op2 != NULL)
            fprintf(file, ", %s", MIPS_Operand(instr->op2));
        if (instr->op3 != NULL)
            fprintf(file, ", %s", MIPS_Operand(instr->op3));
        fprintf(file, "\n");
    }
}
