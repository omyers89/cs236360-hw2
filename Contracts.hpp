#ifndef __CONTRACTS_H
#define __CONTRACTS_H

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <map>



using namespace std;

typedef enum{_BOOL, _INT, _BYTE, _STRING, _VOID} varType;
typedef enum{_FUNC, _IF, _WHILE, _CASE} scopeType;


typedef struct funcType{
    varType retType;
    vector<varType> args;
};

typedef vector<varType> expList;

typedef struct varData{
    int numVal;
    string stringVal;
    bool boolVal;
    string varName;
    varType type;
    funcType func;
    expList expTypes;
}STYPE;


#define YYSTYPE STYPE
#define MAXBYTE 256
#define MAXINTLENGTH 11

#endif