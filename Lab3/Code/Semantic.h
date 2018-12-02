#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

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
char* Semantic_Get_Type_Info(Type* type_id);

/* Process the semantic analysis */
void Semantic_Analysis();

/* Deepth-first traversal to the whole syntax tree */
void Semantic_DFS(TreeNode* cur_root);

/* Deepth-first traversal for ExtDef branch */
void Semantic_DFS_Extern_Defined(TreeNode* cur_root);

/* Deepth-first traversal for ExtDefList branch */
void Semantic_DFS_Extern_Declared_List(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal for FunDec branch */
void Semantic_DFS_Func_Declared(TreeNode* cur_root, Type* rtn, bool declared_only);

/* Deepth-first traversal for VarList branch */
FuncParamList* Semantic_DFS_Var_List(TreeNode* cur_root);

/* Deepth-first traversal for ParamList branch */
Type* Semantic_DFS_Param_Declared(TreeNode* cur_root, char **symbol_id);

/* Deepth-first traversal for VarDec branch */
Type* Semantic_DFS_Var_Declared(TreeNode* cur_root, char **symbol_id, Type* type_id);

/* Deepth-first traversal for Specifier branch */
Type* Semantic_DFS_Specifier(TreeNode* cur_root);

/* Deepth-first traversal for StructSpecifier branch */
Structure* Semantic_DFS_Structure_Specifier(TreeNode* cur_root);

/* Deepth-first traversal for Tag branch */
char* Semantic_DFS_Tag(TreeNode* cur_root);

/* Deepth-first traversal for OptTag branch */
char* Semantic_DFS_Opt_Tag(TreeNode* cur_root);

/* Deepth-first traversal to get ID */
char* Semantic_DFS_Id(TreeNode* cur_root);

/* Deepth-first traversal to get integer value */
int Semantic_DFS_Int(TreeNode* cur_root);

/* Deepth-first traversal to get float value */
float Semantic_DFS_Float(TreeNode* cur_root);

/* Deepth-first traversal for DefList branch */
FieldList* Semantic_DFS_Defined_List(TreeNode* cur_root);

/* Deepth-first traversal for Def branch */
FieldList* Semantic_DFS_Defined(TreeNode* cur_root);

/* Deepth-first traversal for DecList branch */
FieldList* Semantic_DFS_Declared_List(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal for Dec branch */
FieldList* Semantic_DFS_Declared(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal for CompSt branch */
void Semantic_DFS_CompSt(TreeNode* cur_root);

/* Deepth-first traversal for Exp branch */
Type* Semantic_DFS_Expression(TreeNode* cur_root);

/* Deepth-first traversal for Args branch */
FuncArgsList* Semantic_DFS_Args(TreeNode* cur_root);

/* Deepth-first traversal for Stmt branch */
void Semantic_DFS_Stmt(TreeNode* cur_root);

#endif