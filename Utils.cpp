//
// Created by Noam on 6/9/2017.
//

#include "Utils.hpp"

bool isByte(varType a){
    return a == _BYTE;
}

bool isInt(varType a){
    return a == _INT;
}

bool isBoolean(varType a){
    return a == _BOOL;
}

bool isString(varType a){
    return a == _STRING;
}

bool areEqualTypes(varType a,varType b){
    return a == b;
}

bool isNumeric(varType a){
    return isInt(a) || isByte(a);
}

char * toString(int num){
    char * buffer = (char*)malloc(MAXINTLENGTH* sizeof(char));
    sprintf(buffer,"%d",num);
    return buffer;
}

std::vector<const char*> getTypeNames(std::vector<varType> vec){
    std::vector<const char*> ret;
    for(int i=0;i<vec.size();++i)
    {
        switch(vec[i])
        {
            case (_BOOL): ret.push_back("bool");
                break;
            case (_INT): ret.push_back("int");
                break;
            case (_BYTE): ret.push_back("byte");
                break;
            case (_STRING): ret.push_back("string");
                break;
            case (_VOID): ret.push_back("void");
                break;
        }
    }
    return ret;
}