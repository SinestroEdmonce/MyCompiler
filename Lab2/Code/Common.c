#include "Common.h"
#include "stdio.h"

int Oct_2_Dec(char* src){
    int res = 0;
    
    int idx;
    int exp_multi = 1;
    for(idx = strlen(src)-1; idx>0; idx--){
        res = res + exp_multi * (src[idx] - '0');
        exp_multi = exp_multi * 8;
    }
    
    return res;
}

int Hex_2_Dec(char* src){
    int res = 0;
    
    int idx;
    int exp_multi = 1;
    for(idx = strlen(src)-1; idx>1; idx--){
        if (src[idx]>='a' && src[idx]<='f'){
            res = res + exp_multi * (10 + src[idx] - 'a');
        }
        else if (src[idx]>='A' && src[idx]<='F'){
            res = res + exp_multi * (10 + src[idx] - 'A');
        }
        else{
            res = res + exp_multi * (src[idx] - '0');
        }
        exp_multi = exp_multi * 16;
    }
    
    return res;
}


float FloatExp_2_FloatCommon(char* src){
    char* decimal_str;
    char* exp_str;

    if (strchr(src, 'e')==NULL){
        decimal_str = strtok(src, "E");
        exp_str = strtok(NULL, "E");
    }
    else{
        decimal_str = strtok(src, "e");
        exp_str = strtok(NULL, "e");
    }

    assert((decimal_str!=NULL) && (exp_str!=NULL));

    float res = atof(decimal_str);
    int exp_num = atoi(exp_str);
    float exp_multi = exp_num>0?10.0:0.1;

    int idx;
    for(idx=0; idx<abs(exp_num); idx++)
        res = res * exp_multi;

    return res;
}