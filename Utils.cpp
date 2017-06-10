//
// Created by Noam on 6/9/2017.
//

#include "Utils.h"

bool isByte(varData a){
    return a.type == _BYTE;
}

bool isInt(varData a){
    return a.type == _INT;
}

bool isBoolean(varData a){
    return a.type == _BOOL;
}

bool isString(varData a){
    return a.type = _STRING;
}

bool areEqualTypes(varData a,varData b){
    return a.type == b.type;
}

bool isNumeric(varData a){
    return isInt(a) || isByte(a);
}

