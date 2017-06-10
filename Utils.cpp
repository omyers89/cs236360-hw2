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

std::vector<char*> getTypeNames(std::vector<varType> vec){
    std::vector<char*> ret;
    for(int i=0;i<v.size();++i)
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