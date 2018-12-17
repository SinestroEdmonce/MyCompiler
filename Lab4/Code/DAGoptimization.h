#ifndef __DAGOPTIMIZATION_H__
#define __DAGOPTIMIZATION_H__

#include "IRgeneration.h"

typedef struct DAG_Node_{
    IROperand* operand;
    IR_TYPE ir_type;
    struct DAG_NodeList_ *parent_left, *parent_right, *parent_assign;    
} DAG_Node;

typedef struct DAG_NodeList_{
    struct DAG_Node_* dag_node;
    struct DAG_NodeList_* next;
} DAG_NodeList;

typedef struct OperandNodeMap_{
    IROperand* operand;
    struct DAG_Node_* dag_node;
    struct OperandNodeMap_* next;
} OperandNodeMap;

void DAG_Optimization();

#endif