#include "SyntaxTree.h"

TreeNode* Node_Initializer(char* node_name, char* value_str, bool flag){
    TreeNode* tmp = malloc(sizeof(TreeNode));
    memset(tmp->value, '\0', sizeof(tmp->value));
    
    /* Assign the node attributes */
    tmp->is_non_ternmial = flag;
    strcpy(tmp->type, node_name);
    strcpy(tmp->value, value_str);
    tmp->child = NULL;
    tmp->sibling = NULL;
    tmp->is_real_value = false;
    tmp->child_num_depend = -1;

    /* Judge whether the node can be treated as a left value */
    if (strcmp(node_name, "ID\0") == 0){
        tmp->left_value = ID_LEFT;
    }
    else{
        tmp->left_value = NOT_LEFT_VALUE;
    }

    /* Store the value as its own type */
    if (strcmp(node_name, "FLOAT\0")==0){
        double f_val = atof(value_str);
        tmp->value_as_its_type.double_value = f_val;
        tmp->is_real_value = true;
    }
    else if (strcmp(node_name, "INT\0")==0){
        int i_val = atoi(value_str);
        tmp->value_as_its_type.int_value = i_val;
        tmp->is_real_value = true;
    }

    /* Whether the node represent non-ternimal */
    if(strlen(value_str)>0){
        tmp->linenum = yylineno;
    }
    else{
        tmp->linenum = -1;
    }

    return tmp;
}

TreeNode* Get_First_Child(TreeNode* parent){
    if (parent!=NULL)
        return parent->child;
    else
        return NULL;
}

TreeNode* Get_First_Sibling(TreeNode* brother){
    if (brother!=NULL)
        return brother->sibling;
    else
        return NULL;
}

TreeNode* Get_Nth_Child(TreeNode* parent, int num){
    if (parent == NULL)
        return NULL;

    TreeNode* pt = parent->child;
    if (pt != NULL){
        int idx = 1;
        for (; (idx<num) && (pt!=NULL); idx++)
            pt = pt->sibling;
        
        if (pt != NULL)
            return pt;
        else
            return NULL;
    }
    else
        return NULL;
}

bool Insert_Child(TreeNode* parent, TreeNode* child){
    if(parent==NULL)
        return false;
    
    if(child==NULL)
        return false;
    
    /* Insert tree nodes, according to their levels */
    TreeNode* bro = Get_First_Child(parent);
    if(bro==NULL){
        parent->child = child;
        parent->linenum = child->linenum;
        return true;
    }
    else{
        return Insert_Sibling(bro, child);
    }
}

bool Insert_Sibling(TreeNode* brother, TreeNode* young){
    while(brother->sibling!=NULL){
        brother = brother->sibling;
    }
    brother->sibling = young;
    return true;
}

bool Preorder_Traversal(TreeNode* cur_root, int layers){

    if(cur_root!=NULL){
        int idx;
        for(idx = 0; idx < layers; idx++)
            printf("  "); 
        
        /* Print syntax tree based on the requirements */
        if(cur_root->is_non_ternmial==true)
            printf("%s (%d)\n", cur_root->type, cur_root->linenum);
        else{
            if(strcmp(cur_root->type, "INT")==0 || strcmp(cur_root->type, "FLOAT")==0 || strcmp(cur_root->type, "ID")==0){
                if (cur_root->is_real_value == true){
                    if (strcmp(cur_root->type, "INT")==0)
                        printf("%s: %d\n", cur_root->type, cur_root->value_as_its_type.int_value);
                    else
                        printf("%s: %f\n", cur_root->type, cur_root->value_as_its_type.double_value);
                }
                else
                    printf("%s: %s\n", cur_root->type, cur_root->value);
            }
            else
                printf("%s\n", cur_root->type);
        }
            
        
        TreeNode *tmp = cur_root->child;
        while(tmp!=NULL){
            Preorder_Traversal(tmp, layers+1);
            tmp = tmp->sibling;
        }
    }
}