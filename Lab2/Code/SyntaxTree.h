#ifndef __SYNTAXTREE_H_
#define __SYNTAXTREE_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

extern int yylineno;

typedef struct Node {
    /* Name */
    char type[32]; 
    /* Value, stored as string */
    char value[128];

    /* Value, stored as its own type */
    union {
        int int_value;
        double double_value;
    } value_as_its_type;
    
    /* Flag for real value,
     * false for not float or int, true for float or int
     */
    bool is_real_value;

    /* Position */
    int linenum;
    /* Its children and its brothers */
    struct Node* child;
    struct Node* sibling;
    /* Flag for non-ternimal, 
     * false for ternimal, true for non-ternimal  
     */
    bool is_non_ternmial;

} TreeNode;

TreeNode* root;

TreeNode* Node_Initializer(char* node_name, char* value_str, bool flag);
TreeNode* Get_First_Child(TreeNode* parent);
TreeNode* Get_First_Sibling(TreeNode* brother);
bool Insert_Child(TreeNode* parent, TreeNode* child);
bool Insert_Sibling(TreeNode* brother, TreeNode* young);
bool Preorder_Traversal(TreeNode* cur_root, int layers);


#endif