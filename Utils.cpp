//
// Created by Noam on 6/9/2017.
//

#include "Utils.hpp"

bool isByte(STYPE a){
    return a.type == _BYTE;
}

bool isInt(STYPE a){
    return a.type == _INT;
}

bool isBoolean(STYPE a){
    return a.type == _BOOL;
}

bool isString(STYPE a){
    return a.type == _STRING;
}

bool areEqualTypes(STYPE a,STYPE b){
    return a.type == b.type;
}

bool isNumeric(STYPE a){
    return isInt(a) || isByte(a);
}

char * toString(int num){
    char * buffer = (char*)malloc(MAXINTLENGTH* sizeof(char));
    sprintf(buffer,"%d",num);
    return buffer;
}
