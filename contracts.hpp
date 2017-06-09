#ifndef __CONTRACTS_H
#define __CONTRACTS_H

#include <string>
using namespace std;

typedef enum{_BOOL, _INT, _BYTE, _STRING, _VOID} varType;
typedef enum{_FUNC, _IF, _WHILE, _CASE} scopeType;
typedef enum{_TRUE, _FALSE} booleanVal;

typedef struct varData{
    int numVal;
    string stringVal;
    booleanVal boolVal;
    string varName;
    varType type;
}STYPE;

#define YYSTYPE STYPE

#endif