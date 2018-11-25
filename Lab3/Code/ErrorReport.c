#include "ErrorReport.h"

const char* ERROR_EXPLANATION_FORMAT[] = {
    NULL,
    "Undefined variable.",
    "Undefined function.",
    "Redefined variable.",
    "Redefined function.",
    "Type mismatched for assignment.",
    "The left-hand side of an assignment must be a variable.",
    "Type mismatched for operands.",
    "Type mismatched for return.",
    "The function is not applicable for some arguments.",
    "Not an array.",
    "Not a function.",
    "Not an integer.",
    "Illegal usage.",
    "Non-existent field.",
    "Redefined field/Initialized variable in structure.",
    "Duplicated names.",
    "Undefined structure.",
    "Undefined function.",
    "Inconsistent declaration of function.",
};

void Report_Errors(int error_type, TreeNode* tree_node){
    printf("Error type %d at Line %d: ", error_type, tree_node->linenum);
    printf("%s\n", ERROR_EXPLANATION_FORMAT[error_type]);
}