#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "SyntaxTree.h"
#include "ErrorReport.h"
#include "SymbolTable.h"


#define CHILD(tree_node, num) \
    (num == 1?tree_node->child:Get_Nth_Child(tree_node, nnum))
#define TYPE_STR_LENGTH 128

/* Obtain the information of the given type_id */
char* Get_Type_Info(Type* type_id);

/* Process the semantic analysis */
void Semantic_Analysis();

/* Deepth-first traversal to the whole syntax tree */
void DFS(TreeNode* cur_root);

/* Deepth-first traversal TODO */
void DFS_Extern_Defined(TreeNode* cur_root);

/* Deepth-first traversal TODO */
void DFS_Extern_Declared_List(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal TODO */
void DFS_Func_Declared(TreeNode* cur_root, Type* rtn, bool declared_only);

/* Deepth-first traversal TODO */
FuncParamList* DFS_Var_List(TreeNode* cur_root);

/* Deepth-first traversal TODO */
Type* DFS_Param_Declared(TreeNode* cur_root, char **symbol_id);

/* Deepth-first traversal TODO */
Type* DFS_Var_Declared(TreeNode* cur_root, char **symbol_id, Type* type_id);

/* Deepth-first traversal TODO */
Type* DFS_Specifier(TreeNode* cur_root);

/* Deepth-first traversal TODO */
Structure* DFS_Structure_Specifier(TreeNode* cur_root);

/* Deepth-first traversal TODO */
char* DFS_Tag(TreeNode* cur_root);

/* Deepth-first traversal TODO */
char* DFS_Opt_Tag(TreeNode* cur_root);

/* Deepth-first traversal TODO */
char* DFS_Id(TreeNode* cur_root);

/* Deepth-first traversal TODO */
int DFS_Int(TreeNode* cur_root);

/* Deepth-first traversal TODO */
float DFS_Float(TreeNode* cur_root);

/* Deepth-first traversal TODO */
FieldList* DFS_Defined_List(TreeNode* cur_root);

/* Deepth-first traversal TODO */
FieldList* DFS_Defined(TreeNode* cur_root);

/* Deepth-first traversal TODO */
FieldList* DFS_Declared_List(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal TODO */
FieldList* DFS_Declared(TreeNode* cur_root, Type* type_id);

/* Deepth-first traversal TODO */
void DFS_Compst(TreeNode* cur_root);

/* Deepth-first traversal TODO */
Type* DFS_Expression(TreeNode* cur_root);

/* Deepth-first traversal TODO */
FuncArgsList* DFS_Args(TreeNode* cur_root);

/* Deepth-first traversal TODO */
void DFS_Stmt(TreeNode* cur_root);

#endif