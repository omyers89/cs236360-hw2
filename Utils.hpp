//
// Created by Noam on 6/9/2017.
//

#ifndef CS236360_HW2_UTILS_H
#define CS236360_HW2_UTILS_H
#include "Contracts.hpp"

bool areEqualTypes(STYPE a,STYPE b);
bool isBoolean(STYPE a);
bool isNumeric(STYPE a);
bool isString(STYPE a);
bool isInt(STYPE a);
bool isByte(STYPE a);
bool validateFunc(std::vector<varType,string> argV,std::vector<varType> expV);
char* toString(int num);
std::vector<char*> getTypeNames(std::vector<varType> vec);

#endif //CS236360_HW2_UTILS_H
