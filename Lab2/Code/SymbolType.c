#include "SymbolType.h"

Type* Create_Type_Basic(char* basic_id){
    Type* type = NULL;
    if (strcmp(basic_id, "int") == 0){
        Type* type = malloc(sizeof(Type));
        type->kind = BASIC;
        type->basic = TYPE_INT;
    }
    else if (strcmp(basic_id, "float") == 0){
        Type* type = malloc(sizeof(Type));
        type->kind = BASIC;
        type->basic = TYPE_FLOAT;
    }
    else{
        Type* type = malloc(sizeof(Type));
        type->kind = BASIC;
        type->basic = TYPE_OTHERS;
    }
    return type;
}