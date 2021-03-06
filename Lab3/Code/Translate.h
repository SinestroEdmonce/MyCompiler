#ifndef _TRANSLATE_H__
#define _TRANSLATE_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include "SyntaxTree.h"
#include "ErrorReport.h"
#include "SymbolTable.h"


#define CHILD(tree_node, num) \
    ((num == 1)?tree_node->child:Get_Nth_Child(tree_node, num))
#define TYPE_STR_LENGTH 128

/* Obtain the information of the given type_id */
char* Translate_Get_Type_Info(Type* type_id);

/* Process the semantic analysis */
void Translate_Analysis();

/* Deepth-first traversal to the whole syntax tree */
void Translate_DFS(TreeNode* cur_root);

/* Deepth-first traversal for ExtDef branch */
void Translate_DFS_Extern_Defined(TreeNode* cur_root);

/* Deepth-first traversal for ExtDefList branch */
void Translate_DFS_Extern_Declared_List(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal for FunDec branch */
void Translate_DFS_Func_Declared(TreeNode* cur_root, Type* rtn, bool declared_only);

/* Deepth-first traversal for VarList branch */
FuncParamList* Translate_DFS_Var_List(TreeNode* cur_root);

/* Deepth-first traversal for ParamList branch */
Type* Translate_DFS_Param_Declared(TreeNode* cur_root, char **symbol_id);

/* Deepth-first traversal for VarDec branch */
Type* Translate_DFS_Var_Declared(TreeNode* cur_root, char **symbol_id, Type* type_id);

/* Deepth-first traversal for Specifier branch */
Type* Translate_DFS_Specifier(TreeNode* cur_root);

/* Deepth-first traversal for StructSpecifier branch */
Structure* Translate_DFS_Structure_Specifier(TreeNode* cur_root);

/* Deepth-first traversal for Tag branch */
char* Translate_DFS_Tag(TreeNode* cur_root);

/* Deepth-first traversal for OptTag branch */
char* Translate_DFS_Opt_Tag(TreeNode* cur_root);

/* Deepth-first traversal to get ID */
char* Translate_DFS_Id(TreeNode* cur_root);

/* Deepth-first traversal to get integer value */
int Translate_DFS_Int(TreeNode* cur_root);

/* Deepth-first traversal to get float value */
float Translate_DFS_Float(TreeNode* cur_root);

/* Deepth-first traversal for DefList branch */
FieldList* Translate_DFS_Defined_List(TreeNode* cur_root);

/* Deepth-first traversal for Def branch */
FieldList* Translate_DFS_Defined(TreeNode* cur_root);

/* Deepth-first traversal for DecList branch */
FieldList* Translate_DFS_Declared_List(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal for Dec branch */
FieldList* Translate_DFS_Declared(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal for CompSt branch */
void Translate_DFS_CompSt(TreeNode* cur_root);

/* Deepth-first traversal for Exp branch */
Type* Translate_DFS_Expression(TreeNode* cur_root, IROperand* operand);

/* Deepth-first traversal for Args branch */
FuncArgsList* Translate_DFS_Args(TreeNode* cur_root);

/* Deepth-first traversal for Stmt branch */
void Translate_DFS_Stmt(TreeNode* cur_root);

/* The function is used to obtain the memory size that the variable or the data type is going to occupy */
int Get_Type_Size(Type* type); 

/* Obtain the RELOP type from the expression */
RELOP_TYPE Get_Relop(TreeNode* tree_node, bool flag);

/* Obtain the structure's information to determine the memory size that structure member occupys */
unsigned int Get_Field_Offset(Structure* structure, char* symbol_id);

/* Deepth-first traversal for Exp branch, only aiming at CONDITION Expression */
Type* Translate_DFS_Expression_Condition(TreeNode* cur_root, IROperand* label_true, IROperand* label_false);

/* Deepth-first traversal for Exp branch, only aiming at LEFT_VALUE Expression */
Type* Translate_DFS_Expression_Address(TreeNode* cur_root, IROperand* operand);

#endif
