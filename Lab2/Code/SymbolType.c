#include "SymbolType.h"

void Create_Type_Basic(Type** type, char* basic_id){
    if (strcmp(basic_id, "int") == 0){
        *type = malloc(sizeof(Type));
        (*type)->kind = BASIC;
        (*type)->basic = TYPE_INT;
    }
    else if (strcmp(basic_id, "float") == 0){
        *type = malloc(sizeof(Type));
        (*type)->kind = BASIC;
        (*type)->basic = TYPE_FLOAT;
    }
    else{
        *type = malloc(sizeof(Type));
        (*type)->kind = BASIC;
        (*type)->basic = TYPE_OTHERS;
    }
}