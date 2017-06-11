#ifndef __CONTRACTS_H
#define __CONTRACTS_H

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <map>

using namespace std;

typedef enum{_BOOL, _INT, _BYTE, _STRING, _VOID} varType;
typedef enum{_FUNC, _IF, _WHILE, _CASE, _NEST} scopeType;




typedef struct{
	vector<varType> argTypes;
	vector<varType> argNames;
} varList;

typedef struct {
    int numVal;
    string stringVal;
    bool boolVal;
    bool isDeclaration;
    string varName;
    varType type;
	vector<varType> expTypes;
    varList formals;
}STYPE;


#define YYSTYPE STYPE
#define MAXBYTE 256
#define MAXINTLENGTH 11
#define LIBPRINT "print"
#define LIBPRINTI "printi"

#endif