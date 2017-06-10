//
// Created by Noam on 6/9/2017.
//

#include "Utils.h"

bool areEqualTypes(varData a,varData b){
    return a.type == b.type;
}

bool isBoolean(varData a){
    return a.type == _BOOL;
}

bool isNumeric(varData a){
    return a.type == _INT || a.type == _BYTE;
}

bool isString(varData a){
    return a.type = _STRING;
}