#ifndef __SYMBOLTYPE_H_
#define __SYMBOLTYPE_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "SyntaxTree.h"
#include "IRgeneration.h"

/* Declarations for structure definition,
 * specific details showed below.
 */
struct Type_;
struct FieldList_;

/* Structure for different fields in programs */
typedef struct FieldList_ {
    char* field_name;
    /* Type of the field */
    struct Type_* field_type;
    /* prev: for convenience of deletion
     * next: for embedded fields 
     */
    struct FieldList_* prev;
    struct FieldList_* next;
} FieldList;

typedef struct ArraySizeList_ {
    int size;
    /* prev: for convenience of deletion
     * next: for next arary size [..]
     */
    struct ArraySizeList_* prev;
    struct ArraySizeList_* next;
} ArraySizeList;

/* Structure for STRUCTURE in syntax tree */
typedef struct Structure_ {
    struct FieldList_* fields;
} Structure;

/* Structure for formal parameters in a function */
typedef struct FuncParamList_ {
    struct Type_* param_type;
    /* Name of the parameter */
    char* param_name;
    /* prev: for convenience of deletion
     * next: for next parameters
     */
    struct FuncParamList_* prev;
    struct FuncParamList_* next;
} FuncParamList;

/* Structure for different TYPEs or functions in syntax tree */
typedef struct Type_ {
    enum {BASIC, ARRAY, STRUCTURE, FUNCTION, UNKNOWN} kind;
    /* Different types use different groups of variables */
    union {
        enum {TYPE_INT, TYPE_FLOAT, TYPE_OTHERS} basic;
        struct {
            /* Array elments' type */
            struct Type_* elem;
            /* Array size list */
            struct ArraySizeList_* array_size;
        } array;
        /* Structure type */
        struct Structure_* structure;
        struct {
            /* Type of return value of a function */
            struct Type_* rtn;
            /* Parameters list of a fuction*/
            struct FuncParamList_* param_list;
        } func;
        char unknown[128];
    };
} Type;

/* Structure for Arguments in functions */
typedef struct FuncArgsList_ {
    struct Type_* args_type;
    /* prev: for convenience of deletion
     * next: for next parameters
     */
    struct FuncArgsList_* prev;
    struct FuncArgsList_* next;
    
    /* Store every argument's operand */
    IROperand* operand;
} FuncArgsList;

typedef struct StructureSymbol_ {
    char* structure_name;
    struct Structure_* structure_type;
} StructureSymbol;

/* Structure for symbols recorded in the symbol table */
typedef struct SymbolRecord_ {
    /* Record name */
    char* record_name;
    /* Scope level */
    int scope_level;
    /* Type of scope or variables*/
    struct Type_* symbol_type;
    /* Syntax tree node for the scope of some functions */
    TreeNode* tree_node;
    /* For variable symbol only */
    IROperand* operand;
} SymbolRecord;

/* Create a node that belongs to BASIC */
void Create_Type_Basic(Type** type, char* basic_id);


#endif